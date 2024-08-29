/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:47:13 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/20 00:08:33 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_data(t_tokenizer_data *td, t_root *r)
{
	td->ptr = r->line;
	td->type = 'a';
}

static int	finish_tokenizer(t_tokenizer_data *td, t_root *r)
{
	t_token	*ptr;
	char	*last_arg;

	if (r->stoken || td->type != 'a')
	{
		if (token_createadd(&r->token_lst, td->type,
				ft_strdup(r->stoken)) != 0)
			exit_with_standard_error(r, "malloc", errno, 0);
	}
	ptr = r->token_lst;
	last_arg = "";
	while (ptr)
	{
		if (ptr->type == 'a')
			last_arg = ptr->content;
		ptr = ptr->next;
	}
	update_env("_", last_arg, &r->envp);
	return (0);
}

void	tokenize_line(t_root *r)
{
	t_tokenizer_data	td;

	init_data(&td, r);
	while (*td.ptr)
	{
		if (*td.ptr == '\'' || *td.ptr == '\"')
			parse_quotes(&td, r, *td.ptr);
		else if (*td.ptr == '$' && td.type != '-' && td.type != '_')
			parse_expansions(&td, r);
		else if (ft_strchr(TOKEN_CHARS, *td.ptr))
			parse_redirs_pipes(&td, r);
		else if (ft_strchr(SPACES, *td.ptr))
			parse_spaces(&td, r);
		else
		{
			if (update_token(&r->stoken, ft_strldup(td.ptr, 1)) != 0)
				exit_with_standard_error(r, "malloc", errno, 0);
			td.ptr += 1;
		}
	}
	if (finish_tokenizer(&td, r) != 0)
		return ;
	free(r->stoken);
	r->stoken = NULL;
}
