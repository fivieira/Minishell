/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:23:08 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/08 18:57:44 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_node(t_node *node);

static void	free_exec(t_exec *node)
{
	t_redir	*ptr;
	t_redir	*tmp;

	ft_lstclear(&node->argv, free);
	ptr = node->redirs;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		free(tmp->file);
		free(tmp);
	}
	free(node);
}

static void	free_pipe(t_pipe *node)
{
	if (!node)
		return ;
	free_node(node->left);
	free_node(node->right);
	free(node);
}

static void	free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->type == PIPE)
		free_pipe((t_pipe *)node);
	else if (node->type == EXEC)
		free_exec((t_exec *)node);
}

void	free_tree(t_node **tree)
{
	free_node(*tree);
	*tree = NULL;
}
