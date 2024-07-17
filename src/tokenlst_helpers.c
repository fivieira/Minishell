/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlst_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:05:25 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/17 10:42:26 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_tokenlst(t_token *tokenlst, bool free_content)
{
	t_token	*tmp;
	
	while (tokenlst)
	{
		if (free_content)
			free(tokenlst->content);
		tmp = tokenlst;
		tokenlst = tokenlst->next;
		free(tmp);
	}
}

t_token	*ft_tokennew(char type, char *content)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->content = content;
	token->next = NULL;
	return (token);
}

t_token *ft_tokenlast(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

void	ft_tokenadd_back(t_token **token, t_token *new)
{
	if (!(*token))
		*token = new;
	else
		ft_tokenlast(*token)->next = new;
}

int	ft_token_createadd(t_token **tokenlst, char type, char *tokenstr)
{
	t_token	*new;

	new = ft_tokennew(type, tokenstr);
	if (!new)
		return (1);
	ft_tokenadd_back(tokenlst, new);
	return (0);
}
