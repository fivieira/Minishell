/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:25:41 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/13 21:43:30 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;
	int		result;

	a = 0;
	result = 0;
	while (a < n)
	{
		result = (unsigned char)s1[a] - (unsigned char)s2[a];
		if (result || s1[a] == '\0')
			return (result);
		a++;
	}
	return (result);
}
