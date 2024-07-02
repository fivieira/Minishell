/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:47:53 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/02 21:18:23 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_char_env(char c)
{
	return ((c >= 'A' && c <='Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_');
} //AKA isalphanum LMAO

int	ft_expand_env(char **cmd, char **token, char **envp)
{
	int	count;
	char	*value;

	count = 0;
	*cmd += 1;
	while (is_char_env((*cmd)[count]))
		count++;
	value = ft_getenv(ft_strndup(*cmd, count), envp);
	if (!value)
	{
		return (0);
	}
	*token = ft_strjoin(*token, value);
	(*cmd) += count;
	return (ft_strlen(value));
}

int	get_quoted(char **cmd, char **token, char c, char **envp)
{
	char	*start;
	char	*tmp;
	int	count;

	count = 0;
	*cmd += 1;
	start = *cmd;
	while (**cmd != c)
	{
		if (c == '\"' && **cmd == '$')
		{
			tmp = (char *)ft_calloc(count + 1, sizeof(char));
			ft_strlcpy(tmp, start, count + 1);
			*token = ft_strjoin(*token, tmp);
			count += ft_expand_env(cmd, token, envp);
			start = *cmd;
		}
		else if (**cmd == '\0')
			return (-1); //TODO: SYNTAX ERROR: QUOTE NOT CLOSED
		else
		{
			count++;
			*cmd += 1;
		}
	}
	// TODO: CANNOT USE 'COUNT' HERE: AFTER EXPAND, COUNT IS MUCH BIGGER
	// THAN NECESSARY AND CATCHES ANY CHARS AFTER THE END OF THE ENV VAR
	// SO IT PRINTS THEM WHEN IT SHOULDNT
	tmp = (char *)ft_calloc(count + 1, sizeof(char));
	ft_strlcpy(tmp, start, count + 1);
	ft_printf("%s\n", tmp);
	*token = ft_strjoin(*token, tmp);
	free(tmp);
	*cmd += 1;

	return (count);
}

char	*str_cappend(char* str, char c)
{
	char	*out;
	int	len;

	len = ft_strlen(str);
	out = (char *)ft_calloc(len + 2, sizeof(char));
	ft_strlcpy(out, str, len + 1);
	out[len] = c;
	return (out);
}

char    *clean_input(char *cmd, char **envp)
{
        char    *out;
	char	*token;
        int     flags;
        int     count;

        out = ft_strdup("");
	token = ft_strdup("");
        flags = (1 << F_PIPE) | (1 << F_SPACE);
	count = 0;
        if (!out)
                return (NULL); //TODO: DEAL WITH ERROR
        while (*cmd)
        {
		if (is_fon(flags, F_OPEN_SINGLE))
		{
			count += get_quoted(&cmd, &token, '\'', envp);
			set_flag(&flags, F_OPEN_SINGLE, false);
		}
		else if (is_fon(flags, F_OPEN_DOUBLE))
		{
			count += get_quoted(&cmd, &token, '\"', envp);
			set_flag(&flags, F_OPEN_DOUBLE, false);
		}
		else if (*cmd == '\'')
			set_flag(&flags, F_OPEN_SINGLE, true);
		else if (*cmd == '\"')
		{
			set_flag(&flags, F_OPEN_DOUBLE, true);
		}
		else if (*cmd == ' ')
		{
			if (!is_fon(flags, F_SPACE))
			{
				out = ft_strjoin(out, ft_itoa(count));
				out = str_cappend(out, '\"');
				out = ft_strjoin(out, token);
				count = 0;
				free(token);
				token = ft_strdup("");
				set_flag(&flags, F_SPACE, true);
			}
			cmd += 1;
			continue;
		}
		else if (*cmd == '$')
		{
			count += ft_expand_env(&cmd, &token, envp);
		}
		else
		{
			token = str_cappend(token, *cmd); 
			count++;
			cmd += 1;
		}
		set_flag(&flags, F_SPACE, false);
        }
	if (count)
	{
		out = ft_strjoin(out, ft_itoa(count));
		out = str_cappend(out, '\"');
		out = ft_strjoin(out, token); //TODO; MAYBE I CAN BUILD THIS WITH LISTS INSTEAD??
	}
	return (out); //TODO: FIX LEAKS
}
