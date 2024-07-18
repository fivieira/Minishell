/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:56:02 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/18 12:52:48 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	prtstr_env(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = -1;
	while (array[++i] != NULL)
	{
		if (ft_strchr(array[i], '='))
			ft_printf("%s\n", array[i]);
	}
}
