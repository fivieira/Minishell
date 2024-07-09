/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:47:53 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/09 23:07:59 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_expand_env(char **cmd, char **token, char **envp)
{
	int		count;
	char	*value;

	count = 0;
	*cmd += 1;
	while (ft_isalnum((*cmd)[count]) || (*cmd)[count] == '_')
		count++;
	if (ft_getenv(ft_strndup(*cmd, count), &value, envp) != 0)
		return (free(token), 1);
	(*cmd) += count;
	if (!value)
		return (0);
	*token = ft_strjoin_free(*token, value);
	if (*token == NULL)
		return (1);
	return (0);
}

int	update_token(char **token, char *start, int len)
{
	char	*tmp;

	tmp = (char *)ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (1);
	ft_strlcpy(tmp, start, len + 1);
	*token = ft_strjoin_free(*token, tmp);
	if (!(*token))
		return (1);
	return (0);
}

int	get_quoted(char **cmd, char **token, char c, char **envp)
{
	char	*start;

	*cmd += 1;
	start = *cmd;
	while (**cmd != c)
	{
		if (c == '\"' && **cmd == '$')
		{
			if (update_token(token, start, *cmd - start) != 0
					|| ft_expand_env(cmd, token, envp) != 0)
				return (ft_printf("MALLOC ERROR\n"), 1);
			start = *cmd;
		}
		else if (**cmd == '\0')
			return (ft_printf("SYNTAX ERROR\n"), 1);
		else
			*cmd += 1;
	}
	if (update_token(token, start, *cmd - start) != 0)
		return (ft_printf("MALLOC ERROR\n"), 1);
	*cmd += 1;
	return (0);
}

int	parse_spaces(t_tokenizer_data *td)
{
	t_token	*new;

	if (*td->tokenstr)
	{
		new = ft_tokennew(td->type, td->tokenstr);
		if (!new)
			return (1);
		ft_tokenadd_back(&td->tokenlst, new);
		td->type = 'a';
		td->tokenstr = ft_strdup("");
		if (!td->tokenstr)
			return (1);
	}
	td->cmd += 1;
	return (0);
}	

int	parse_redirs_pipes(t_tokenizer_data *td)
{
	if (td->type != 'a')
		return (ft_printf("SYNTAX ERROR\n"), 1);
	if (*td->tokenstr)
	{
		ft_tokenadd_back(&td->tokenlst, ft_tokennew(td->type, td->tokenstr));
		td->tokenstr = ft_strdup("");
	}
	if (*td->cmd == '|')
	{
		ft_tokenadd_back(&td->tokenlst, ft_tokennew('|', NULL));
		td->cmd += 1;
	}
	else if (*td->cmd == '<')
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
	while (*td->cmd == ' ')
		td->cmd += 1;
	return (0);
}

static void	init_data(t_tokenizer_data *td, char *cmd)
{
	td->cmd = cmd;
	td->tokenlst = NULL;
	td->type = 'a';
	td->tokenstr = ft_strdup("");
}

t_token	*tokenizer(char *cmd, char **envp)
{
	t_tokenizer_data	td;
	int			status;

	init_data(&td, cmd);
	while (*td.cmd)
	{
		if (*td.cmd == '\'')
			status = get_quoted(&td.cmd, &td.tokenstr, '\'', envp);
		else if (*td.cmd == '\"')
			status = get_quoted(&td.cmd, &td.tokenstr, '\"', envp);
		else if (*td.cmd == '$')
			status = ft_expand_env(&td.cmd, &td.tokenstr, envp);
		else if (ft_strchr("><|", *td.cmd))
			status = parse_redirs_pipes(&td);
		else if (*td.cmd == ' ')
			status = parse_spaces(&td);
		else
		{
			status = update_token(&td.tokenstr, td.cmd, 1);
			td.cmd += 1;
		}
		if (status != 0)
			return (NULL); //TODO: Deal with error
	}
	if (*td.tokenstr)
		ft_tokenadd_back(&td.tokenlst, ft_tokennew(td.type, td.tokenstr));
	return (td.tokenlst);
}
