/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:51:00 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/10 19:51:42 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_length(const char *str, size_t size);

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_length;
	size_t	src_length;

	dst_length = get_length(dst, size);
	src_length = get_length(src, INT_MAX);
	if (dst_length == size)
		return (dst_length + src_length);
	i = 0;
	while (dst_length + i < size - 1 && *src)
	{
		dst[dst_length + i] = *src;
		src++;
		i++;
	}
	dst[dst_length + i] = '\0';
	return (dst_length + src_length);
}

static size_t	get_length(const char *str, size_t size)
{
	size_t	count;

	count = 0;
	while (str[count] && count < size)
		count++;
	return (count);
}
