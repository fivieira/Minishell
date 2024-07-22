/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:43:14 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/17 13:35:39 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenizer_exit(char *line, t_tokenizer_data *td)
{
	free(line);
	ft_free_tokenlst(td->tokenlst, true);
	if (td->tokenstr)
		free(td->tokenstr);
	exit(td->status);
}

void	tree_builder_exit(t_root *r, int exit_code, char *error_msg)
{
	if (error_msg)
		perror(error_msg);
	free(r->line);
	ft_free_tokenlst(r->organized, true);
	ft_free_tree(r->tree);
	exit(exit_code);
}
