/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:49:48 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/17 07:46:34 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		b;
	const char	*s;
	char		*d;

	b = 0;
	s = src;
	d = dest;
	while (b < n)
	{
		d[b] = s[b];
		b++;
	}
	return (dest);
}
