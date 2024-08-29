/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_parsers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:15:38 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/26 17:18:10 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_in_quotes(t_root *r, t_tokenizer_data *td, int i)
{
	char	*env_value;

	if (i != 0 && update_token(&r->stoken,
			ft_strldup(td->ptr, i)) != 0)
		exit_with_standard_error(r, "malloc", errno, 0);
	td->ptr += i;
	env_value = expand_cmd_env(td, r);
	if (!env_value && !errno)
	{
		if (update_token(&r->stoken, ft_strdup("")) != 0)
			exit_with_standard_error(r, "malloc", errno, 0);
	}
	else if (update_token(&r->stoken, env_value) != 0)
		exit_with_standard_error(r, "malloc", errno, 0);
	if (errno)
		exit_with_standard_error(r, "malloc", errno, 0);
}

void	parse_quotes(t_tokenizer_data *td, t_root *r, char c)
{
	int		i;

	td->ptr += 1;
	i = -1;
	while (td->ptr[++i] != c)
	{
		if (c == '\"' && td->ptr[i] == '$'
			&& td->type != '-' && td->type != '_')
		{
			expand_in_quotes(r, td, i);
			i = -1;
		}
	}
	if (update_token(&r->stoken, ft_strldup(td->ptr, i)) != 0)
		exit_with_standard_error(r, "malloc", errno, 0);
	if (td->type == '-')
		td->type = '_';
	td->ptr += i + 1;
}
