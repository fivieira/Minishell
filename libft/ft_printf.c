/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 07:19:25 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/02 09:02:01 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>

static int	print_format(const char conv, va_list args);
static int	ft_putmemad_fd(void *memad, int fd);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format += 1;
			len += print_format(*format, args);
		}
		else
			len += write(1, format, 1);
		format += 1;
	}
	va_end(args);
	return (len);
}

static int	print_format(const char conv, va_list args)
{
	if (conv == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (conv == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	else if (conv == 'p')
		return (ft_putmemad_fd(va_arg(args, void *), 1));
	else if (conv == 'd' || conv == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (conv == 'u')
		return (ft_putnbr_base_fd(
				(long)va_arg(args, unsigned int),
				"0123456789", 1));
	else if (conv == 'x')
		return (ft_putnbr_base_fd(
				(long)va_arg(args, unsigned int),
				"0123456789abcdef", 1));
	else if (conv == 'X')
		return (ft_putnbr_base_fd(
				(long)va_arg(args, unsigned int),
				"0123456789ABCDEF", 1));
	else if (conv == '%')
		return (write(1, "%", 1));
	return (0);
}

static int	write_converted(unsigned long l_nbr, int divisor,
			char *base, int fd)
{
	int	mod;
	int	len;

	len = 0;
	mod = l_nbr % divisor;
	if (l_nbr == 0)
		return (0);
	len += write_converted((l_nbr / divisor), divisor, base, fd);
	return (len + write(1, &base[mod], fd));
}

static int	ft_putmemad_fd(void *memad, int fd)
{
	int				len;
	unsigned long	ul;

	if (memad == NULL)
		return (write(fd, "(nil)", 5));
	len = write(fd, "0x", 2);
	ul = (unsigned long)memad;
	len += write_converted(ul, 16, "0123456789abcdef", fd);
	return (len);
}
