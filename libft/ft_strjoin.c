/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:57:35 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/11 15:44:36 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		s1_len;
	size_t		s2_len;
	size_t		final_str_size;
	char		*final_str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	final_str_size = s1_len + s2_len + 1;
	final_str = (char *)malloc(final_str_size * sizeof(char));
	if (final_str == NULL)
		return (NULL);
	ft_strlcpy(final_str, s1, final_str_size);
	ft_strlcat(final_str, s2, final_str_size);
	return (final_str);
}
