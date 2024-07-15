/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:43:57 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/09 15:02:22 by ndo-vale         ###   ########.fr       */
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
