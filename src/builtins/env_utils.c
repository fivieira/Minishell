/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:27:38 by fivieira          #+#    #+#             */
/*   Updated: 2024/08/20 16:53:45 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_key_from_var(char *var)
{
	int	i;

	i = -1;
	if (!var)
		return (NULL);
	while (var[++i] && var[i] != '='
		&& !(var[i] == '+' && var[i + 1] == '='))
		continue ;
	return (ft_strldup(var, i));
}

int	is_key_valid(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	while (key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
	}
	return (i);
}

int	get_envp_i_from_key(char *key, char **envp)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	if (!is_key_valid(key))
		return (-1);
	i = -1;
	if (!envp)
		return (-1);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0
			&& (*(envp[i] + key_len) == '\0' || *(envp[i] + key_len) == '='))
			return (i);
	}
	return (-1);
}
