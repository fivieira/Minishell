/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:17:36 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/25 19:13:51 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	**ft_matrix_dup(void **matrix)
{
	char	**matrix_str;
	char	**dup;
	int		i;
	int		size;

	matrix_str = (char **)matrix;
	i = -1;
	while (matrix_str[++i])
		continue ;
	size = i + 1;
	dup = (char **)ft_calloc(size, sizeof(char *));
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < size - 1)
	{
		dup[i] = ft_strldup(matrix_str[i], ft_strlen(matrix_str[i]));
		if (!(dup[i]))
			return (ft_matrix_free((void ***)(&dup)), NULL);
	}
	return ((void **)dup);
}
