/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:47:53 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/09 20:26:05 by ndo-vale         ###   ########.fr       */
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
	int		count;

	count = 0;
	*cmd += 1;
	start = *cmd;
	while (*(*cmd + count) != c)
	{
		if (c == '\"' && **cmd == '$')
		{
			*cmd += count;
			if (update_token(token, start, count) != 0
					|| ft_expand_env(cmd, token, envp) != 0)
				return (ft_printf("MALLOC ERROR\n"), 1);
			count = 0;
			start = *cmd;
		}
		else if (*(*cmd + count) == '\0')
			return (ft_printf("SYNTAX ERROR\n"), 1);
		else
			count++;
	}
	if (update_token(token, start, count) != 0)
		return (ft_printf("MALLOC ERROR\n"), 1);
	*cmd += count + 1;
	return (0);
}

int	parse_spaces(char **token, t_token **tokenlst, char *type, char **cmd)
{
	t_token	*new;

	if (**token)
	{
		new = ft_tokennew(*type, *token);
		if (!new)
			return (1);
		ft_tokenadd_back(tokenlst, new);
		*type = 'a';
		*token = ft_strdup("");
		if (!(*token))
			return (1);
	}
	*cmd += 1;
	return (0);
}	

int	parse_redirs_pipes(char **token, t_token **tokenlst, char *type, char **cmd)
{
	if (*type != 'a')
		return (ft_printf("SYNTAX ERROR\n"), 1);
	if (**token)
	{
		ft_tokenadd_back(tokenlst, ft_tokennew(*type, *token));
		*token = ft_strdup("");
	}
	if (**cmd == '|')
	{
		ft_tokenadd_back(tokenlst, ft_tokennew('|', NULL));
		*cmd += 1;
	}
	else if (**cmd == '<')
	{
		*cmd += 1;
		if (**cmd == '<')
		{
			*type = '-';
			*cmd += 1;
		}
		else
			*type = '<';
	}
	else
	{
		*cmd += 1;
		if (**cmd == '>')
		{
			*type = '+';
			*cmd += 1;
		}
		else
			*type = '>';
	}
	while (**cmd == ' ')
		*cmd += 1;
	return (0);
}

t_token	*tokenizer(char *cmd, char **envp)
{
	t_token	*out;
	char	type;
	char	*token;
	int		status;

	out = NULL;
	type = 'a';
	token = ft_strdup("");
	while (*cmd)
	{
		if (*cmd == '\'')
			status = get_quoted(&cmd, &token, '\'', envp);
		else if (*cmd == '\"')
			status = get_quoted(&cmd, &token, '\"', envp);
		else if (*cmd == '$')
			status = ft_expand_env(&cmd, &token, envp);
		else if (ft_strchr("><|", *cmd))
			status = parse_redirs_pipes(&token, &out, &type, &cmd);
		else if (*cmd == ' ')
			status = parse_spaces(&token, &out, &type, &cmd);
		else
		{
			status = update_token(&token, cmd, 1);
			cmd += 1;
		}
		if (status != 0)
			return (NULL); //TODO: Deal with error
	}
	ft_tokenadd_back(&out, ft_tokennew(type, token));
	return (out);
}
