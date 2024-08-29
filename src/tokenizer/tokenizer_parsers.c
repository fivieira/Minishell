/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:03:29 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/26 17:18:29 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_expansions(t_tokenizer_data *td, t_root *r)
{
	char	*env_value;

	env_value = expand_cmd_env(td, r);
	if (env_value)
	{
		if (tokenize_env(r, td, env_value) != 0)
		{
			free(env_value);
			exit_with_standard_error(r, "malloc", errno, 0);
		}
		free(env_value);
	}
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
