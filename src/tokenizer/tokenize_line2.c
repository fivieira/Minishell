/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:05:51 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/12 20:54:20 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_token(char **token, char *start)
{
	if (!start)
		return (-1);
	if (!(*token))
		*token = start;
	else
	{
		*token = ft_strjoin_free(*token, start);
		if (!(*token))
			return (-1);
	}
	return (0);
}

int	tokenize_env(t_root *r, t_tokenizer_data *td, char *env_value)
{
	int	i;

	i = -1;
	while (env_value[++i])
	{
		if (ft_strchr(SPACES, env_value[i]))
		{
			if (i != 0 && update_token(&r->stoken,
					ft_strldup(env_value, i)) != 0)
				return (-1);
			if (i != 0 && token_createadd(&r->token_lst,
					td->type, r->stoken) != 0)
				return (-1);
			r->stoken = NULL;
			env_value += i + 1;
			i = -1;
		}
	}
	if (i != 0 && update_token(&r->stoken,
			ft_strldup(env_value, i)) != 0)
		return (-1);
	return (0);
}

char	*expand_exit_code(t_tokenizer_data *td, t_root *r)
{
	char	*code;

	code = ft_itoa(r->prev_exit_code);
	if (!code)
		return (NULL);
	td->ptr += 1;
	return (code);
}

char	*expand_cmd_env(t_tokenizer_data *td, t_root *r)
{
	char	*env_value;

	td->ptr += 1;
	if (*(td->ptr) == '?')
		env_value = expand_exit_code(td, r);
	else if (ft_isdigit(*(td->ptr)))
	{
		if (*(td->ptr) == '0')
			env_value = ft_strdup("minishell");
		else
			env_value = NULL;
		td->ptr += 1;
	}
	else
	{
		errno = 0;
		env_value = get_env_value(td->ptr, r->envp);
		td->ptr += get_env_key_len(td->ptr);
	}
	if (errno)
		exit_with_standard_error(r, "malloc", errno, 0);
	return (env_value);
}
