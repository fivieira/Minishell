/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:38:20 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/12 10:45:25 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_variable_index_recursive(const char *name, char **env, int i)
{
	if(env[i] == NULL)
		return (-1);
	if(ft_strncmp(name, env[i], ft_strlen(name)) == 0 && \
		env[i][ft_strlen(name)] == '=' || \
			env[i][ft_strlen(name)] == '\0')
		return (i);
	return (find_variable_index_recursive(name, env, i + 1));	
}

bool	isvar_valid(const char *name)
{
	if (name == NULL || ft_isdigit(*name))
		return (false);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}
