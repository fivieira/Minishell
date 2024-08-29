/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 20:17:33 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/20 00:28:04 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_option(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0])
		return (arg[0] == '-' && arg[1]);
	return (0);
}

void	delete_var(char *key, char **envp)
{
	int	var_i;

	var_i = get_envp_i_from_key(key, envp);
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
