/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:08:05 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/14 10:57:57 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	a;
	int		result;

	a = 0;
	result = 0;
	while (a < n)
	{
		result = ((unsigned char *)s1)[a] - ((unsigned char *)s2)[a];
		if (result)
			return (result);
		a++;
	}
	return (result);
}
