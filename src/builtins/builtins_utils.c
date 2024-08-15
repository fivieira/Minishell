/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 20:17:33 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/14 20:40:22 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_key_valid(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	while (key[++i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
	}
	return (1);
}

int	get_envp_i(char *key, char **envp)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	if (!is_key_valid(key))
		return (-1);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0)
			return (i);
	}
	return (-1);
}

void	delete_var(char *var, char **envp)
{
	int	var_i;

	var_i = get_envp_i(var, envp);
	if (var_i >= 0)
	{
		free(envp[var_i]);
		while (envp[++var_i])
			envp[var_i - 1] = envp[var_i];
		envp[var_i - 1] = NULL;
	}
}

t_builtin	get_builtin(char *cmd)
{
	static char	*builtins[BUILTINS_AM + 1] = {
		"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};
	static int	(*builtin_funcs[BUILTINS_AM + 1])(char **, char ***) = {
		&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset,
		&ft_env, &ft_exit, NULL};
	int			i;

	i = -1;
	if (!cmd)
		return (NULL);
	while (builtins[++i])
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i]) + 1) == 0)
			return (builtin_funcs[i]);
	}
	return (NULL);
}

int	run_builtin(t_list *argv_lst, char ***envp)
{
	char	**args;
	int		status;

	args = create_args(argv_lst);
	if (!args)
		return (errno);
	status = get_builtin(args[0])(args, envp);
	ft_matrix_free((void ***)&args);
	return (status);
}
