/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:47:53 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/17 13:40:09 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	update_token(char **token, char *start, int len)
{
	char	*tmp;

	tmp = (char *)ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (perror("malloc"), 1);
	ft_strlcpy(tmp, start, len + 1);
	if (!(*token))
		*token = tmp;
	else
	{
		*token = ft_strjoin_free(*token, tmp);
		if (!(*token))
			return (perror("malloc"), 1);
	}
	return (0);
}

int	get_quoted(char **cmd, char **token, char **envp)
{
	char	*start;
	char	c;

	c = **cmd;
	*cmd += 1;
	start = *cmd;
	while (**cmd != c)
	{
		if (c == '\"' && **cmd == '$')
		{
			if (update_token(token, start, *cmd - start) != 0
				|| ft_expand_env(cmd, token, envp) != 0)
				return (errno);
			start = *cmd;
		}
		else if (**cmd == '\0')
			return (ft_putstr_fd(SYNTAX_ERROR, 2), 2);
		else
			*cmd += 1;
	}
	if (update_token(token, start, *cmd - start) != 0)
		return (errno);
	*cmd += 1;
	return (0);
}

static void	init_data(t_tokenizer_data *td, char *cmd)
{
	td->cmd = cmd;
	td->tokenlst = NULL;
	td->type = 'a';
	td->tokenstr = NULL;
}

static int	finish_tokenizer(t_tokenizer_data *td)
{
	if (ft_strchr("<>+-", td->type) && !td->tokenstr)
		return (ft_putstr_fd(SYNTAX_ERROR, 2), 2);
	if (td->tokenstr)
	{
		if (ft_token_createadd(&td->tokenlst, td->type, td->tokenstr) != 0)
			return (perror("malloc"), errno);
	}
	if (ft_tokenlast(td->tokenlst) && ft_tokenlast(td->tokenlst)->type == '|')
		return (ft_putstr_fd(SYNTAX_ERROR, 2), 2);
	return (0);
}

t_token	*tokenizer(char *cmd, char **envp)
{
	t_tokenizer_data	td;

	init_data(&td, cmd);
	while (*td.cmd)
	{
		if (*td.cmd == '\'' || *td.cmd == '\"')
			td.status = get_quoted(&td.cmd, &td.tokenstr, envp);
		else if (*td.cmd == '$' && td.type != '-')
			td.status = ft_expand_env(&td.cmd, &td.tokenstr, envp);
		else if (ft_strchr("><|", *td.cmd))
			td.status = parse_redirs_pipes(&td);
		else if (*td.cmd == ' ')
			td.status = parse_spaces(&td);
		else
		{
			td.status = update_token(&td.tokenstr, td.cmd, 1);
			td.cmd += 1;
		}
		if (td.status != 0)
			tokenizer_exit(cmd, &td);
	}
	td.status = finish_tokenizer(&td);
	if (td.status != 0)
		tokenizer_exit(cmd, &td);
	return (td.tokenlst);
}
