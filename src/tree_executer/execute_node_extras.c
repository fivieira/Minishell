/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node_extras.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:09:15 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/09 13:04:13 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	int	status;
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
