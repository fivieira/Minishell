/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:46:32 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/17 14:58:56 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_pipe(t_pipe *node)
{
	if (!node)
		return ;
	ft_free_tree(node->left);
	ft_free_tree(node->right);
	free(node);
}

static void	free_redir(t_redir *node)
{
	if (!node)
		return ;
	ft_free_tree(node->cmd);
	free(node->file);
	free(node);
}

void	ft_free_tree(t_cmd *node)
{
	if (!node)
		return ;
	if (node->type == PIPE)
		free_pipe((t_pipe *)node);
	else if (node->type == REDIR)
		free_redir((t_redir *)node);
	else if (node->type == EXEC)
	{
		ft_lstclear(&((t_exec *)node)->argv, free);
		free(node);
	}
}
