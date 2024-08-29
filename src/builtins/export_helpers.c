/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:09:41 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/21 18:32:26 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_envs(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

int	fill_new_envp(char **new, char ***old_ref)
{
	char	**old;
	int		i;

	old = *old_ref;
	i = -1;
	while (old[++i])
		new[i] = old[i];
	return (i);
}

char	**copy_envs(char **envp)
{
	int		count;
	char	**new_envp;
	int		i;

	count = count_envs(envp);
	new_envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i > 0)
				free(new_envp[--i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = (NULL);
	return (new_envp);
}

void	print_sorted_envs(char **sorted_envp)
{
	int		i;
	char	*key_equals;
	char	*value;

	i = 0;
	while (sorted_envp[i])
	{
		if (sorted_envp[i][0] == '_')
		{
			i++;
			continue ;
		}
		key_equals = ft_strldup(sorted_envp[i],
				get_env_key_len(sorted_envp[i]) + 1);
		value = ft_strdup(sorted_envp[i] + ft_strlen(key_equals));
		ft_printf("declare -x %s", key_equals);
		if (key_equals[get_env_key_len(sorted_envp[i])] == '=')
			ft_printf("\"%s\"", value);
		ft_printf("\n");
		free(key_equals);
		free(value);
		i++;
	}
}

void	bubble_sort_envs(char **envp)
{
	int		n;
	int		i;
	int		j;
	bool	swapped;

	n = count_envs(envp);
	i = 0;
	while (i < n - 1)
	{
		swapped = false;
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strncmp(envp[j], envp[j + 1], ft_strlen(envp[j])) > 0)
			{
				ft_swap(&envp[j], &envp[j + 1]);
				swapped = true;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}
