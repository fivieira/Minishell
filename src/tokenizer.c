/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:47:53 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/16 22:57:02 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_token_createadd(t_token **tokenlst, char type, char *tokenstr)
{
	t_token	*new;

	new = ft_tokennew(type, tokenstr);
	if (!new)
		return (1);
	ft_tokenadd_back(tokenlst, new);
	return (0);
}

int	ft_expand_env(char **cmd, char **token, char **envp)
{
	int		count;
	char	*value;

	count = 0;
	*cmd += 1;
	while (ft_isalnum((*cmd)[count]) || (*cmd)[count] == '_')
		count++;
	if (!count)
		return (update_token(token, (*cmd) - 1, 1));
	if (ft_getenv(ft_strndup(*cmd, count), &value, envp) != 0)
		return (errno);
	(*cmd) += count;
	if (!value)
		return (0);
	if (!(*token))
	{
		*token = value;
		return (0);
	}
	*token = ft_strjoin_free(*token, value);
	if (*token == NULL)
		return (perror("malloc"), errno);
	return (0);
}

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

void	free_line_exit(char *line, int status)
{
	free(line);
	exit(status);
}

t_token	*tokenizer(char *cmd, char **envp)
{
	t_tokenizer_data	td;

	init_data(&td, cmd);
	while (*td.cmd)
	{
		if (*td.cmd == '\'' || *td.cmd == '\"')
			td.status = get_quoted(&td.cmd, &td.tokenstr, envp);
		else if (*td.cmd == '$')
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
			free_line_exit(cmd, td.status);
	}
	td.status = finish_tokenizer(&td);
	if (td.status != 0)
		free_line_exit(cmd, td.status);
	return (td.tokenlst);
}
