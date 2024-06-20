/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:11:23 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/14 12:02:26 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_first_i(char const *s, char const *set);
static size_t	get_last_i(char const *s, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*final_str;
	size_t	first_i;
	size_t	last_i;
	size_t	final_size;

	first_i = get_first_i(s1, set);
	if (first_i == ft_strlen(s1))
	{
		final_str = (char *)malloc(1 * sizeof(char));
		if (final_str == NULL)
			return (NULL);
		*final_str = '\0';
		return (final_str);
	}
	last_i = get_last_i(s1, set);
	final_size = (last_i + 1 - first_i) + 1;
	final_str = (char *)malloc(final_size * sizeof(char));
	if (final_str == NULL)
		return (NULL);
	ft_strlcpy(final_str, &s1[first_i], final_size);
	return (final_str);
}

static size_t	get_first_i(char const *s, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_strlen(s))
	{
		j = 0;
		while (j < ft_strlen(set) && s[i] != set[j])
			j++;
		if (j == ft_strlen(set))
			break ;
		i++;
	}
	return (i);
}

static size_t	get_last_i(char const *s, char const *set)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s) - 1;
	while (i > 0)
	{
		j = 0;
		while (j < ft_strlen(set) && s[i] != set[j])
			j++;
		if (j == ft_strlen(set))
			break ;
		i--;
	}
	return (i);
}
