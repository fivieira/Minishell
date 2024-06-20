/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:00:24 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/18 21:29:39 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_nbr(long l, int fd);

int	ft_putnbr_fd(int n, int fd)
{
	long	l;
	int		is_neg;

	l = n;
	is_neg = 0;
	if (l == 0)
		return (write(fd, "0", 1));
	if (l < 0)
	{
		write(fd, "-", 1);
		l *= -1;
		is_neg = 1;
	}
	return (write_nbr(l, fd) + is_neg);
}

static int	write_nbr(long l, int fd)
{
	char	c;
	int		len;

	len = 0;
	if (l > 0)
	{
		len += write_nbr(l / 10, fd);
		c = (l % 10) + '0';
		return (len + write(fd, &c, 1));
	}
	return (0);
}
