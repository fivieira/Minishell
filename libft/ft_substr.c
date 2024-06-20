/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:34:44 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/16 08:01:22 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			subs_len;
	char			*subs;
	unsigned int	i;

	if (start > ft_strlen(s) || *s == '\0')
		return (ft_strdup(""));
	subs_len = len;
	if (len > ft_strlen(s) - start)
		subs_len = ft_strlen(s) - start;
	subs = (char *)malloc((subs_len + 1) * sizeof(char));
	if (subs == NULL)
		return (NULL);
	i = 0;
	while (i < subs_len)
	{
		subs[i] = s[i + start];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
