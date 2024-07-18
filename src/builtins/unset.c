/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:42:32 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/18 12:51:30 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset_variable(const char *variable, t_localenv *local)
{
	int	index;

	index = find_variable_index_recursive(variable, local->sort, 0);
	if (index != -1)
	{
		free(local->sort[index]);
		if (index >= 0)
		{
			while (local->sort[index] != NULL)
			{
				local->sort[index] = local->sort[index + 1];
				index++;
			}
		}
		local->sort[index] = NULL;
	}
	return (EXIT_SUCCESS);
}

int	unset_variable2(const char *variable, t_localenv *local)
{
	int	index;

	index = find_variable_index_recursive(variable, local->content, 0);
	if (index != -1)
	{
		free(local->content[index]);
		if (index >= 0)
		{
			while (local->content[index] != NULL)
			{
				local->content[index] = local->content[index + 1];
				index++;
			}
		}
		local->content[index] = NULL;
	}
	return (0);
}

int	command_unset(char **comands, t_localenv *local)
{
	int	i;

	if (comands == NULL || local == NULL || local->content == NULL)
		return (1); // tratar erro com os sinais
	if (comands[1] == NULL)
		return (EXIT_SUCCESS);
	if (!isvar_valid(comands[1]))
		return (0);
	i = 1;
	while (comands[i] != NULL)
	{
		if (unset_variable(comands[i], local) != 0)
			return (EXIT_FAILURE); // tratar com sinal
		if (unset_variable2(comands[i], local) != 0)
			return (EXIT_FAILURE); // tratar com sinal
		i++;
	}
	return (EXIT_SUCCESS);
}
