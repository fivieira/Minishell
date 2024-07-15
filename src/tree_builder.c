/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:04:21 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/15 17:02:51 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*parse_redir(t_cmd *cmd, t_token **ptr)
{
	char	c;

	c = (*ptr)->type;
	if (c == '<')
		cmd = redir_cmd(cmd, (*ptr)->content, O_RDONLY, 0);
	else if (c == '-')
		;//TODO: IMPLEMENT HEREDOC
	else if (c == '>')
		cmd = redir_cmd(cmd, (*ptr)->content, O_WRONLY|O_CREAT|O_TRUNC, 1);
	else if (c == '+')
		cmd = redir_cmd(cmd, (*ptr)->content, O_WRONLY|O_CREAT|O_APPEND, 1);
	return (cmd);
}

t_cmd	*parse_exec(t_token **ptr, char **envp)
{
	t_cmd	*full_cmd;
	t_exec	*exec_node;

	full_cmd = exec_cmd(envp);
	exec_node = (t_exec *)full_cmd;
	full_cmd = parse_redir(full_cmd, ptr);
	while (*ptr && (*ptr)->type != '|')
	{
		if ((*ptr)->type == 'a')
			ft_lstadd_back(&(exec_node->argv), ft_lstnew((*ptr)->content));
		else
			full_cmd = parse_redir(full_cmd, ptr);
		*ptr = (*ptr)->next;
	}
	return (full_cmd);
}

t_cmd	*parse_pipe(t_token **ptr, char **envp)
{
	t_cmd	*node;

	node = parse_exec(ptr, envp);
	if (*ptr && (*ptr)->type == '|')
	{
		*ptr = (*ptr)->next;
		node = pipe_cmd(node, parse_pipe(ptr, envp));
	}
	return (node);
}

t_cmd	*tree_builder(t_token *tokenlst, char **envp)
{
	t_cmd	*tree;

	tree = parse_pipe(&tokenlst, envp);
	return (tree);
}
