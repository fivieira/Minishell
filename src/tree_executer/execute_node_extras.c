/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node_extras.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:09:15 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/19 23:56:32 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect(t_redir *node, t_root *r)
{
	int	fd;

	fd = open(node->file, get_redir_mode(node->redir_type), 0644);
	if (fd == -1)
	{
		if (errno == 2)
		{
			r->exit_code = 1;
			perror(node->file);
			return (-1);
		}
		exit_with_standard_error(r, node->file, 1, 0);
	}
	if (dup2(fd, get_redir_fd(node->redir_type)) < 0)
	{
		close(fd);
		exit_with_standard_error(r, "dup", errno, 0);
	}
	close(fd);
	return (0);
}

void	apply_pipe_and_execute(t_node *node, t_root *r, int *p,
		int multipurp_fd)
{
	if (dup2(p[multipurp_fd], multipurp_fd) == -1)
	{
		close(p[0]);
		close(p[1]);
		exit_with_standard_error(r, "dup", errno, 0);
	}
	close(p[0]);
	close(p[1]);
	execute_node(node, r);
}

void	failed_execve_aftermath(char *cmd_path, char **args, t_root *r)
{
	int		status;
	char	*cmd;

	cmd = ft_strdup(args[0]);
	if (!cmd)
	{
		free(cmd_path);
		exit_with_standard_error(r, "malloc", errno, 0);
	}
	status = errno;
	ft_matrix_free((void ***)&args);
	free(cmd_path);
	errno = 0;
	if (status == 2)
		exit_with_custom_error(r, cmd, CMD_NOT_FOUND_MSG, 127);
	else if (status == 13)
		exit_with_custom_error(r, cmd, PERMISSION_DENIED_MSG, 126);
	exit_with_standard_error(r, "execve", 1, 0);
}
