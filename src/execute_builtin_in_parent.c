/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_in_parent.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:54:31 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/19 22:57:55 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	save_original_fds(t_root *r)
{
	r->original_stdin = dup(STDIN_FILENO);
	if (r->original_stdin < 0)
	{
		return (-1);
	}
	r->original_stdout = dup(STDOUT_FILENO);
	if (r->original_stdout < 0)
	{
		close(r->original_stdin);
		return (-1);
	}
	return (0);
}

static int	revert_to_original_fds(t_root *r)
{
	if (dup2(r->original_stdout, STDOUT_FILENO) < 0)
		return (-1);
	if (dup2(r->original_stdin, STDIN_FILENO) < 0)
		return (-1);
	close(r->original_stdin);
	close(r->original_stdout);
	return (0);
}

void	execute_builtin_in_parent(t_root *r)
{
	t_exec	*exec_node;

	exec_node = (t_exec *)r->tree;
	if (save_original_fds(r) != 0)
		exit_with_standard_error(r, "dup", errno, 0);
	if (execute_redirs(exec_node->redirs, r) != 0)
	{
		close(r->original_stdout);
		close(r->original_stdin);
		free_tree(&r->tree);
		return ;
	}
	if (ft_strncmp(exec_node->argv->content, "exit", 5) == 0)
		ft_exit_parent(r, exec_node);
	else
		r->exit_code = run_builtin(((t_exec *)r->tree)->argv, &r->envp);
	if (errno)
		exit_with_standard_error(r, "builtin", errno, 0);
	free_tree(&r->tree);
	if (revert_to_original_fds(r) != 0)
		exit_with_standard_error(r, "dup", errno, 0);
}
