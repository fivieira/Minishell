/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:24:23 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/12 10:32:36 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n);
static void	write_nbr(char *nbr, long l, int len);

char	*ft_itoa(int n)
{
	int		len;
	long	l;
	char	*nbr;

	len = get_len(n);
	nbr = (char *)malloc((len + 1) * sizeof(char));
	if (nbr == NULL)
		return (NULL);
	l = n;
	if (l == 0)
		*nbr = '0';
	if (l < 0)
	{
		*nbr = '-';
		l *= -1;
	}
	nbr[len] = '\0';
	write_nbr(nbr, l, len - 1);
	return (nbr);
}

static int	get_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	write_nbr(char *nbr, long l, int len)
{
	while (l > 0)
	{
		nbr[len--] = (l % 10) + '0';
		l /= 10;
	}
}
