/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:20:39 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/18 21:28:25 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	count_val_base(char *str);
static int	write_converted(long nbr, int divisor, char *base, int fd);

int	ft_putnbr_base_fd(long nbr, char *base, int fd)
{
	long	l_nbr;
	int		divisor;
	int		len;

	len = 0;
	l_nbr = nbr;
	divisor = count_val_base(base);
	if (divisor < 2)
		return (0);
	if (l_nbr == 0)
		return (write(1, &base[0], fd));
	else if (l_nbr < 0)
	{
		len += write(1, "-", fd);
		l_nbr = -l_nbr;
	}
	return (len + write_converted(l_nbr, divisor, base, fd));
}

static int	count_val_base(char *str)
{
	int	count1;
	int	count2;

	count1 = 0;
	while (str[count1])
	{
		if (str[count1] == '-' || str[count1] == '+')
			return (0);
		count2 = count1 + 1;
		while (str[count2])
		{
			if (str[count1] == str[count2])
				return (0);
			count2++;
		}
		count1++;
	}
	return (count1);
}

static int	write_converted(long l_nbr, int divisor, char *base, int fd)
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
