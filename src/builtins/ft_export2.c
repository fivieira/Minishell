/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:35:27 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/20 18:26:24 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_export_envs(char **envp)
{
	int		i;
	char	**sorted_envp;

	sorted_envp = copy_envs(envp);
	if (!sorted_envp)
		return (errno);
	bubble_sort_envs(sorted_envp);
	print_sorted_envs(sorted_envp);
	i = -1;
	while (sorted_envp[++i])
		free(sorted_envp[i]);
	free(sorted_envp);
	return (0);
}

static void	join_both_values(char **arg_ptr, char **envp, char *arg_key)
{
	char	*old_value;
	char	*arg_value;

	old_value = get_env_value(arg_key, envp);
	arg_value = ft_strdup(ft_strnstr(*arg_ptr, "+=",
				ft_strlen(*arg_ptr)) + 2);
	free(*arg_ptr);
	*arg_ptr = ft_strjoin_free(ft_strjoin(arg_key, "="),
			ft_strjoin_free(old_value, arg_value));
	delete_var(arg_key, envp);
	free(arg_key);
	return ;
}

static void	assign_new_value(char **arg_ptr, char **envp, char *arg_key)
{
	char	*arg_value;

	arg_value = ft_strdup(ft_strnstr(*arg_ptr, "+=",
				ft_strlen(*arg_ptr)) + 2);
	free(*arg_ptr);
	*arg_ptr = ft_strjoin_free(ft_strjoin(arg_key, "="), arg_value);
	delete_var(arg_key, envp);
	free(arg_key);
}

void	append_env_var(char **arg_ptr, char **envp)
{
	int		i;
	char	*arg_key;
	char	*arg_value;

	arg_key = get_env_key(*arg_ptr);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], arg_key, ft_strlen(arg_key)) == 0
			&& envp[i][ft_strlen(arg_key)] == '=')
		{
			join_both_values(arg_ptr, envp, arg_key);
			return ;
		}
		else if (ft_strncmp(envp[i], arg_key, ft_strlen(arg_key)) == 0
			&& envp[i][ft_strlen(arg_key)] == '\0')
		{
			assign_new_value(arg_ptr, envp, arg_key);
			return ;
		}
	}
	arg_value = ft_strdup(ft_strnstr(*arg_ptr, "+=", ft_strlen(*arg_ptr)) + 1);
	free(*arg_ptr);
	*arg_ptr = ft_strjoin_free(arg_key, arg_value);
}
