/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_constructors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:38:18 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/30 10:19:44 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir	*create_redir(char *file, char redir_type)
{
	t_redir	*redir_node;

	redir_node = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir_node)
		return (NULL);
	redir_node->type = REDIR;
	redir_node->file = file;
	redir_node->redir_type = redir_type;
	redir_node->next = NULL;
	return (redir_node);
}

t_exec	*create_exec(void)
{
	t_exec	*exec_node;

	exec_node = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!exec_node)
		return (NULL);
	exec_node->type = EXEC;
	exec_node->redirs = NULL;
	exec_node->argv = NULL;
	return (exec_node);
}

t_pipe	*create_pipe(t_node *left, t_node *right)
{
	t_pipe	*pipe_node;

	pipe_node = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!pipe_node)
		return (free(left), NULL);
	pipe_node->type = PIPE;
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}
