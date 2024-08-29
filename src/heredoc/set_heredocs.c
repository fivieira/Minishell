/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:18:31 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/19 23:16:12 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_heredoc_in_pipe(t_node *node, t_root *r)
{
	t_pipe	*pipe_node;
	int		status;

	pipe_node = (t_pipe *)node;
	status = set_heredocs(pipe_node->left, r);
	if (status)
		return (status);
	status = set_heredocs(pipe_node->right, r);
	if (status)
		return (status);
	return (0);
}

static int	find_heredoc_in_redirs(t_node *node, t_root *r)
{
	t_redir	*redir_node;

	redir_node = ((t_exec *)node)->redirs;
	while (redir_node)
	{
		if (redir_node->redir_type == '-' || redir_node->redir_type == '_')
		{
			redir_node->file = heredoc(redir_node->file,
					r, redir_node->redir_type);
			if (!redir_node->file)
				return (r->exit_code);
		}
		redir_node = redir_node->next;
	}
	return (0);
}

int	set_heredocs(t_node *node, t_root *r)
{
	int	status;

	status = 0;
	if (node->type == PIPE)
		status = find_heredoc_in_pipe(node, r);
	else
		status = find_heredoc_in_redirs(node, r);
	return (status);
}
