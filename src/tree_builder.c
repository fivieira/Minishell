/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:04:21 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/22 18:14:18 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*parse_redir(t_cmd *cmd, t_token **ptr, t_root *r)
{
	char	c;
	t_redir	*rptr;

	c = (*ptr)->type;
	if (c == '<')
		cmd = redir_cmd(cmd, (*ptr)->content, O_RDONLY, 0);
	else if (c == '-')
		cmd = redir_cmd(cmd, (*ptr)->content, O_RDONLY, 0);
	else if (c == '>')
		cmd = redir_cmd(cmd, (*ptr)->content, O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (c == '+')
		cmd = redir_cmd(cmd, (*ptr)->content, O_WRONLY | O_CREAT | O_APPEND, 1);
	if (!cmd)
		tree_builder_exit(r);
	rptr = (t_redir *)cmd;
	while (rptr->cmd->type != EXEC)
		rptr = (t_redir *)rptr->cmd;
	rptr->redir_type = c;
	return (cmd);
}

t_cmd	*parse_exec(t_token **ptr, t_root *r)
{
	t_cmd	*full_cmd;
	t_exec	*exec_node;

	full_cmd = exec_cmd(r->envp);
	if (!full_cmd)
		tree_builder_exit(r);
	exec_node = (t_exec *)full_cmd;
	while (*ptr && (*ptr)->type != '|')
	{
		if ((*ptr)->type == 'a')
		{
			if (ft_lstadd_back(&(exec_node->argv), ft_lstnew((*ptr)->content)) != 0)
				tree_builder_exit(r); //TODO: fix segfault
		}
		else
			full_cmd = parse_redir(full_cmd, ptr, r);
		*ptr = (*ptr)->next;
	}
	return (full_cmd);
}

t_cmd	*parse_pipe(t_token **ptr, t_root *r)
{
	t_cmd	*node;

	node = parse_exec(ptr, r);
	if (!node)
		tree_builder_exit(r);
	if (*ptr && (*ptr)->type == '|')
	{
		*ptr = (*ptr)->next;
		node = pipe_cmd(node, parse_pipe(ptr, r));
		if (!node)
			tree_builder_exit(r);
	}
	return (node);
}

void	tree_builder(t_root *r)
{
	t_token	*ptr;

	ptr = r->organized;
	r->tree = parse_pipe(&ptr, r);
	ft_free_tokenlst(r->organized, false);
	find_heredocs(r->tree, r->tree, r->envp);
}
