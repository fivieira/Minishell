/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:03:29 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/13 11:41:48 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_quotes(t_tokenizer_data *td, t_root *r, char c)
{
	int	i;

	td->ptr += 1;
	i = -1;
	while (td->ptr[++i] != c)
	{
		if (c == '\"' && td->ptr[i] == '$' && td->type != '-' && td->type != '_')
		{
			if (i != 0 && update_token(&r->stoken,
					ft_strldup(td->ptr, i)) != 0)
				exit_with_standard_error(r, "malloc", errno, 0);
			td->ptr += i;
			char *env_value;
			env_value = expand_cmd_env(td, r);
			if (update_token(&r->stoken, env_value) != 0)
				exit_with_standard_error(r, "malloc", errno, 0);
			i = -1;
		}
	}
	if (update_token(&r->stoken, ft_strldup(td->ptr, i)) != 0)
		exit_with_standard_error(r, "malloc", errno, 0);
	if (td->type == '-')
		td->type = '_';
	td->ptr += i + 1;
}

static void	parse_redirs(t_tokenizer_data *td)
{
	if (*td->ptr == '<')
	{
		td->ptr += 1;
		if (*td->ptr == '<')
		{
			td->type = '-';
			td->ptr += 1;
		}
		else
			td->type = '<';
	}
	else
	{
		td->ptr += 1;
		if (*td->ptr == '>')
		{
			td->type = '+';
			td->ptr += 1;
		}
		else
			td->type = '>';
	}
}

void	parse_redirs_pipes(t_tokenizer_data *td, t_root *r)
{
	if (r->stoken || td->type != 'a')
	{
		if (token_createadd(&r->token_lst, td->type, r->stoken) != 0)
			exit_with_standard_error(r, "malloc", errno, 0);
		td->type = 'a';
		r->stoken = NULL;
	}
	if (*td->ptr == '|')
	{
		if (token_createadd(&r->token_lst, '|', NULL) != 0)
			exit_with_standard_error(r, "malloc", errno, 0);
		td->ptr += 1;
	}
	else
		parse_redirs(td);
	while (ft_strchr(SPACES, *td->ptr) && *td->ptr != '\0')
		td->ptr += 1;
}

void	parse_spaces(t_tokenizer_data *td, t_root *r)
{
	if (r->stoken)
	{
		if (token_createadd(&r->token_lst, td->type, r->stoken) != 0)
			exit_with_standard_error(r, "malloc", errno, 0);
		td->type = 'a';
		r->stoken = NULL;
	}
	td->ptr += 1;
}
