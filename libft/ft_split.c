/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:01:53 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/18 14:25:58 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**populate_array(char const *s, char c, char **array);
static char		**empty_array(char **array);
static char		*create_str(char const *s, char c);
static size_t	get_subs_am(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	size_t		subs_am;
	char		**array;

	if (!s)
		return (NULL);
	subs_am = get_subs_am(s, c);
	array = (char **)malloc((subs_am + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	if (populate_array(s, c, array) == NULL)
	{
		free(array);
		return (NULL);
	}
	return (array);
}

static char	**populate_array(char const *s, char c, char **array)
{
	int	was_c;
	int	i;

	was_c = 1;
	i = 0;
	while (*s)
	{
		if (*s == c)
		{
			was_c = 1;
			s++;
			continue ;
		}
		else if (was_c)
		{
			array[i] = create_str(s, c);
			if (array[i++] == NULL)
				return (empty_array(array));
		}
		was_c = 0;
		s++;
	}
	array[i] = NULL;
	return (array);
}

static char	**empty_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	return (NULL);
}

static char	*create_str(char const *s, char c)
{
	size_t		len;
	char		*str;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, len + 1);
	return (str);
}

static size_t	get_subs_am(char const *s, char c)
{
	int		was_c;
	size_t	amount;

	was_c = 1;
	amount = 0;
	while (*s)
	{
		if (*s == c)
			was_c = 1;
		else
		{
			if (was_c)
			{
				amount++;
				was_c = 0;
			}
		}
		s++;
	}
	return (amount);
}
