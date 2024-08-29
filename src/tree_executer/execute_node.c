/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:43:14 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/21 18:31:42 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_redirs(t_redir *node, t_root *r)
{
	while (node)
	{
		if (!node->file)
		{
			ft_print_error("ambiguous redirect");
			r->exit_code = 1;
			return (-1);
		}
		if (redirect(node, r) != 0)
			return (-1);
		node = node->next;
	}
	return (0);
}

void	execute_exec(t_exec *node, t_root *r)
{
	char	**args;
	char	*cmd_path;

	if (execute_redirs(node->redirs, r) != 0)
		free_everything_exit(r, 1);
	if (!node->argv)
		free_everything_exit(r, 0);
	try_running_builtin(node, r);
	args = create_args(node->argv);
	if (!args)
		exit_with_standard_error(r, "malloc", errno, 0);
	if (args[0] && args[0][0] == '\0')
	{
		ft_matrix_free((void ***)&args);
		exit_with_custom_error(r, ft_strdup("\'\'"), CMD_NOT_FOUND_MSG, 127);
	}
	cmd_path = validate_cmd(args[0], r->envp);
	if (!cmd_path)
	{
		ft_matrix_free((void ***)&args);
		exit_with_standard_error(r, "echo", errno, 0);
	}
	execve(cmd_path, args, r->envp);
	failed_execve_aftermath(cmd_path, args, r);
}

static void	treat_pipe_aftermath(t_root *r, int status)
{
	if (WIFEXITED(status))
		free_everything_exit(r, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
		free_everything_exit(r, 128 + WTERMSIG(status));
	}
	else
		exit_with_standard_error(r, "something unexpected occured\n", 1, 0);
}

void	execute_pipe(t_pipe *node, t_root *r)
{
	int		p[2];
	pid_t	cpid_l;
	pid_t	cpid_r;
	int		status;

	if (pipe(p) < 0)
		exit_with_standard_error(r, "pipe", errno, 0);
	cpid_l = fork();
	if (cpid_l == -1)
		close_pipe_and_exit(p, r, "fork");
	else if (cpid_l == 0)
		apply_pipe_and_execute(node->left, r, p, 1);
	cpid_r = fork();
	if (cpid_r == -1)
		close_pipe_and_exit(p, r, "fork");
	else if (cpid_r == 0)
		apply_pipe_and_execute(node->right, r, p, 0);
	close(p[0]);
	close(p[1]);
	free_tree(&r->tree);
	free_root(r);
	waitpid(cpid_l, &status, 0);
	waitpid(cpid_r, &status, 0);
	treat_pipe_aftermath(r, status);
}

void	execute_node(t_node *node, t_root *r)
{
	if (node->type == PIPE)
		execute_pipe((t_pipe *)node, r);
	else
		execute_exec((t_exec *)node, r);
}
