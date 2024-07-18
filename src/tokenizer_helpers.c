/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:44:04 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/18 11:44:24 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parse_spaces(t_tokenizer_data *td)
{
	if (td->tokenstr)
	{
		if (ft_token_createadd(&td->tokenlst, td->type, td->tokenstr) != 0)
			return (perror("malloc"), errno);
		td->type = 'a';
		td->tokenstr = NULL;
	}
	td->cmd += 1;
	return (0);
}

void	parse_redirs(t_tokenizer_data *td)
{
	if (*td->cmd == '<')
	{
		td->cmd += 1;
		if (*td->cmd == '<')
		{
			td->type = '-';
			td->cmd += 1;
		}
		else
			td->type = '<';
	}
	else
	{
		td->cmd += 1;
		if (*td->cmd == '>')
		{
			td->type = '+';
			td->cmd += 1;
		}
		else
			td->type = '>';
	}
}

int	parse_redirs_pipes(t_tokenizer_data *td)
{
	if (td->tokenstr)
	{
		if (ft_token_createadd(&td->tokenlst, td->type, td->tokenstr) != 0)
			return (perror("malloc"), errno);
		td->type = 'a';
		td->tokenstr = NULL;
	}
	if (td->type != 'a')
		return (ft_putstr_fd(SYNTAX_ERROR, 2), 2);
	if (*td->cmd == '|')
	{
		if (ft_token_createadd(&td->tokenlst, '|', NULL) != 0)
			return (perror("malloc"), errno);
		td->cmd += 1;
	}
	else
		parse_redirs(td);
	while (*td->cmd == ' ')
		td->cmd += 1;
	return (0);
}
