/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:54:12 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/14 10:50:12 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_same_to_end_s1(const char *s1, const char *s2, size_t len);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;

	a = 0;
	if (*little == '\0')
		return ((char *)big);
	while (*big && a < len)
	{
		if (*big == little[0])
		{
			if (is_same_to_end_s1(little, big, len - a))
			{
				return ((char *)big);
			}
		}
		big++;
		a++;
	}
	return (NULL);
}

static int	is_same_to_end_s1(const char *s1, const char *s2, size_t len)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i] || i == len)
		{
			return (0);
		}
		i++;
	}
	return (1);
}
