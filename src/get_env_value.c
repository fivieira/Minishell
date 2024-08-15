/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:25:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/13 11:14:41 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_env_key_len(char *start)
{
	int	count;

	count = 0;
	if (ft_isdigit(start[0]))
		return (1);
	while (ft_isalnum(start[count]) || start[count] == '_')
		count++;
	return (count);
}

char	*get_env_key(char *start)
{
	int	count;

	if (!start)
		return (NULL);
	if (*start == '?')
		return (ft_strdup("?"));
	count = get_env_key_len(start);
	if (!count)
		return (ft_strdup(""));
	return (ft_strldup(start, count));
}

char	*get_env_value(char *start, char **envp)
{
	char	*key;
	int		len;
	char	**ptr;

	key = get_env_key(start);
	if (!key)
		return (NULL);
	if (*key == '\0')
		return (free(key), ft_strdup("$"));
	if (!envp)
		return (free(key), NULL);
	len = ft_strlen(key);
	ptr = envp;
	while (*ptr)
	{
		if (ft_strncmp(key, *ptr, len) == 0 && (*ptr)[len] == '=')
			return (free(key), ft_strdup(*ptr + len + 1));
		ptr += 1;
	}
	free(key);
	return (NULL);
}

void	update_env(char *name, char *value, char ***envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (((*envp)[i]))
	{
		if (ft_strncmp(name, (*envp)[i], len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strjoin_free(ft_strjoin(name, "="),
					ft_strdup(value));
			return ;
		}
		i++;
	}
}
