/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:47:53 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/04 22:23:06 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*out;

	out = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (out);
}

int	ft_expand_env(char **cmd, char **token, char **envp)
{
	int		count;
	char	*value;

	count = 0;
	*cmd += 1;
	while (ft_isalnum((*cmd)[count]) || (*cmd)[count] == '_')
		count++;
	value = ft_getenv(ft_strndup(*cmd, count), envp);
	if (!value)
	{
		(*cmd) += count;
		return (0);
	}
	*token = ft_strjoin_free(*token, value);
	(*cmd) += count;
	return (count);
}

char	*update_token(char *token, char *start, int size)
{
	char	*tmp;

	tmp = (char *)ft_calloc(size, sizeof(char));
	ft_strlcpy(tmp, start, size);
	return (ft_strjoin_free(token, tmp));
}

int	get_quoted(char **cmd, char **token, char c, char **envp)
{
	char	*start;
	int		count;

	count = 0;
	*cmd += 1;
	start = *cmd;
	while (**cmd != c)
	{
		if (c == '\"' && **cmd == '$')
		{
			*token = update_token(*token, start, count + 1);
			count = 0;
			ft_expand_env(cmd, token, envp);
			start = *cmd;
		}
		else if (**cmd == '\0')
			return (ft_printf("SYNTAX ERROR\n"), -1);
		else
		{
			count++;
			*cmd += 1;
		}
	}
	if (count)
		*token = update_token(*token, start, count + 1);
	*cmd += 1;
	return (count);
}

char	*str_cappend(char *str, char c)
{
	char	*out;
	int		len;

	len = ft_strlen(str);
	out = (char *)ft_calloc(len + 2, sizeof(char));
	ft_strlcpy(out, str, len + 1);
	out[len] = c;
	free(str);
	return (out);
}

t_token	*tokenizer(char *cmd, char **envp)
{
	t_token	*out;
	char	type;
	char	*token;

	out = NULL;
	type = 'a';
	token = ft_strdup("");
	while (*cmd)
	{
		if (*cmd == '\'')
			get_quoted(&cmd, &token, '\'', envp);
		else if (*cmd == '\"')
			get_quoted(&cmd, &token, '\"', envp);
		else if (*cmd == '$')
			ft_expand_env(&cmd, &token, envp);
		else if (ft_strchr("><|", *cmd))
		{
			if (type != 'a')
				return (ft_printf("SYNTAX ERROR\n"), NULL);
			if (*token)
			{
				ft_tokenadd_back(&out, ft_tokennew(type, token));
				token = ft_strdup("");
			}
			if (*cmd == '|')
			{
				ft_tokenadd_back(&out, ft_tokennew('|', NULL));
				cmd += 1;
			}
			else if (*cmd == '<')
			{
				cmd += 1;
				if (*cmd == '<')
				{
					type = '-';
					cmd += 1;
				}
				else
					type = '<';
			}
			else
			{
				cmd += 1;
				if (*cmd == '>')
				{
					type = '+';
					cmd += 1;
				}
				else
					type = '>';
			}
			while (*cmd == ' ')
				cmd += 1;
		}
		else if (*cmd == ' ')
		{
			if (*token)
			{
				ft_tokenadd_back(&out, ft_tokennew(type, token));
				type = 'a';
				token = ft_strdup("");
			}
			cmd += 1;
		}
		else
		{
			token = str_cappend(token, *cmd);
			cmd += 1;
		}
	}
	ft_tokenadd_back(&out, ft_tokennew(type, token));
	return (out);
}
