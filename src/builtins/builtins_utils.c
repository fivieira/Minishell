/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:56:02 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/18 12:52:48 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_end_cmd_builtin(t_cmd *tree)
{
	t_cmd	*ptr;
	t_exec	*exec_node;

	ptr = tree;
	while (ptr->type == REDIR)
	{
		ptr = ((t_redir *)ptr)->cmd;
	}
	exec_node = (t_exec *)ptr;
	if (get_builtin_func_i((char *)exec_node->argv->content) != -1)
		return (true);
	return (false);
}

builtin_ptr	get_builtin(int i)
{
	int     (*builtin_funcs[BUILTINS_AM + 1])(char **, char **);
	
	builtin_funcs[0] = &ft_echo;
        builtin_funcs[1] = &ft_pwd;
        builtin_funcs[2] = &ft_exit;
        builtin_funcs[BUILTINS_AM] = NULL;
        
        return (builtin_funcs[i]);
}

int	get_builtin_func_i(char *cmd)
{
	char    *builtins[BUILTINS_AM + 1];
	int		i;

	i = -1;
	builtins[0] = "echo";
        builtins[1] = "pwd";
        builtins[2] = "exit";
        builtins[BUILTINS_AM] = NULL;

	while (builtins[++i])
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i]) + 1) == 0)
			return (i);
	return (-1);
}

/*void	prtstr_env(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = -1;
	while (array[++i] != NULL)
	{
		if (ft_strchr(array[i], '='))
			ft_printf("%s\n", array[i]);
	}
}*/
