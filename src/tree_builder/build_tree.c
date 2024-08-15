/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:47:22 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/13 12:43:21 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_arg(t_exec *node, t_token *token)
{
	char	*arg;
	t_list	*lst_node;

	arg = ft_strdup(token->content);
	if (!arg)
		return (1);
	lst_node = ft_lstnew(arg);
	if (!lst_node)
		return (free(arg), 1);
	ft_lstadd_back(&node->argv, lst_node);
	return (0);
}

int	add_redir(t_exec *exec_node, t_token *token)
{
	char	*filename;
	t_redir	*node;
	t_redir	*ptr;

	filename = NULL;
	if (token->content)
	{
		filename = ft_strdup(token->content);
		if (!filename)
			return (1);
	}
	node = create_redir(filename, token->type);
	if (!node)
		return (free(filename), 1);
	if (!exec_node->redirs)
		exec_node->redirs = node;
	else
	{
		ptr = exec_node->redirs;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
	}
	return (0);
}

t_node	*parse_exec(t_token **ptr, t_root *r)
{
	t_exec	*node;

	(void)r;
	node = create_exec();
	if (!node)
		return (NULL);
	while (*ptr && (*ptr)->type != '|')
	{
		if ((*ptr)->type == 'a')
		{
			if (add_arg(node, *ptr) != 0)
				return (ft_lstclear(&node->argv, free),
					free(node), NULL);
		}
		else
		{
			if (add_redir(node, *ptr) != 0)
				return (ft_lstclear(&node->argv, free),
					free(node), NULL);
		}
		*ptr = (*ptr)->next;
	}
	return ((t_node *)node);
}

t_node	*parse_pipe(t_token **ptr, t_root *r)
{
	t_node	*node;

	node = parse_exec(ptr, r);
	if (!node)
		return (NULL);
	if (*ptr && (*ptr)->type == '|')
	{
		*ptr = (*ptr)->next;
		node = (t_node *)create_pipe(node, parse_pipe(ptr, r));
		if (!node)
			return (NULL);
	}
	return (node);
}

int	build_tree(t_root *r)
{
	t_token	*ptr;

	ptr = r->token_lst;
	r->tree = parse_pipe(&ptr, r);
	free_tokenlst(&r->token_lst);
	if (!r->tree)
	{
		perror("malloc");
		free_exit(r, errno);
	}
	r->exit_code = set_heredocs(r->tree, r);
	if (errno)
		exit_with_standard_error(r, "heredoc", errno, 0);
	if (r->exit_code)
	{
		free_tree(&r->tree);
		return (1);
	}
	return (0);
}
