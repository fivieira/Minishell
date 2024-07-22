/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:29:55 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/22 18:15:19 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*exec_cmd(char **envp)
{
	t_exec	*exec_node;

	exec_node = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!exec_node)
		return (NULL);
	exec_node->type = EXEC;
	exec_node->envp = envp;
	return ((t_cmd *)exec_node);
}

t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe	*pipe_node;

	pipe_node = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!pipe_node)
		return (NULL);
	pipe_node->type = PIPE;
	pipe_node->left = left;
	pipe_node->right = right;
	return ((t_cmd *)pipe_node);
}

t_cmd	*redir_cmd(t_cmd *cmd, char *file, int mode, int fd)
{
	t_redir	*redir_node;
	t_redir	*ptr;

	redir_node = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir_node)
		return (NULL);
	redir_node->type = REDIR;
	redir_node->file = file;
	redir_node->mode = mode;
	redir_node->fd = fd;
	if (cmd->type == EXEC)
	{
		redir_node->cmd = cmd;
		return ((t_cmd *)redir_node);
	}
	ptr = (t_redir *)cmd;
	while (ptr->cmd->type == REDIR)
		ptr = (t_redir *)ptr->cmd;
	redir_node->cmd = ptr->cmd;
	ptr->cmd = (t_cmd *)redir_node;
	return (cmd);
}
