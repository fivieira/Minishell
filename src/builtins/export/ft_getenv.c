/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:43:57 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/18 12:49:23 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_getenv(const char *name, char **value, char **envp)
{
	size_t	len;
	char	**env_var;

	if (name == NULL || envp == NULL)
		return (value = NULL, 1);
	len = ft_strlen(name);
	env_var = envp;
	while (*env_var)
	{
		if (ft_strncmp(name, *env_var, len) == 0 && (*env_var)[len] == '=')
		{
			*value = ft_strdup(*env_var + len + 1);
			if (!(*value))
				return (1);
			return (0);
		}
		env_var++;
	}
	*value = NULL;
	return (0);
}

int	ft_safe_getenv(char *start, int len, char **value, char **envp)
{
	char	*key;
	int		status;

	key = ft_strndup(start, len);
	if (!key)
		return (1);
	status = ft_getenv(key, value, envp);
	free(key);
	return (status);
}

int	ft_expand_env(char **cmd, char **token, char **envp)
{
	int		count;
	char	*value;

	count = 0;
	*cmd += 1;
	while (ft_isalnum((*cmd)[count]) || (*cmd)[count] == '_')
		count++;
	if (!count)
		return (update_token(token, (*cmd) - 1, 1));
	if (ft_safe_getenv(*cmd, count, &value, envp) != 0)
		return (errno);
	(*cmd) += count;
	if (!value)
		return (0);
	if (!(*token))
	{
		*token = value;
		return (0);
	}
	*token = ft_strjoin_free(*token, value);
	if (*token == NULL)
		return (perror("malloc"), errno);
	return (0);
}
