/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:24:24 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/23 14:48:15 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	**ft_matrix_dup(void **matrix)
{
	char	**matrix_str;
	char	**dup;
	int	i;
	int	size;
	
	matrix_str = (char **)matrix;
	i = -1;
	while (matrix_str[++i])
		continue ;
	size = i + 1;
	dup = (char **)ft_calloc(size, sizeof(char *));
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < size - 1)
	{
		dup[i] = ft_strndup(matrix_str[i], ft_strlen(matrix_str[i]));
		if (!(dup[i]))
			return (ft_free_matrix((void **)dup), NULL);
	}
	return ((void **)dup);
}

int    find_exec_builtin(char **args, char **envp, t_cmd *tree)
{
        int     func_i;
        int     status;
        builtin_ptr     builtin;
        char	**dup;

        status = 0;
        func_i = get_builtin_func_i(args[0]);
        if (func_i == -1)
        {
        	return (127);
        }
	builtin = get_builtin(func_i);
	dup = (char **)ft_matrix_dup((void **)args);
	free(args);
	ft_free_tree(tree);
	status = builtin(dup, envp);
	ft_free_matrix((void **)dup);
	return (status);
}

void    builtin_redir(t_redir *cmd, t_cmd *start)
{
        int     fd;

	(void)start;
        fd = open(cmd->file, cmd->mode, 0644);
        dup2(fd, cmd->fd);
        close(fd);
}

int	exec_parent_builtin(t_cmd *tree)
{
	t_cmd	*ptr;
	t_exec	*exec_node;
        char    **args;

	ptr = tree;
	while (ptr->type == REDIR)
	{
		builtin_redir((t_redir *)ptr, tree);
		ptr = ((t_redir *)ptr)->cmd;
	}
	exec_node = (t_exec *)ptr;
        args = create_args(exec_node->argv, false);
        if (!args)
        {
                perror("malloc");
                ft_free_tree(tree);
                exit(errno);
        }
        return (find_exec_builtin(args, exec_node->envp, tree));
}
