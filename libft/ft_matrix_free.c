/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:27:58 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/24 14:26:08 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matrix_free(void ***matrix)
{
	int	i;

	if (!*matrix)
		return ;
	i = -1;
	while ((*matrix)[++i])
		free((*matrix)[i]);
	free(*matrix);
	*matrix = NULL;
}
