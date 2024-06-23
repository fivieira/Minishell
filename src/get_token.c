/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:54:17 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/23 15:03:36 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	parse_less_than(char **s)
{
	*s += 1;
	if (**s == '<')
	{
		*s += 1;
		return ('-');
	}
	return ('<');
}

static char	parse_more_than(char **s)
{
	*s += 1;
        if (**s == '>')
        {
                *s += 1;
                return ('+');
        }
        return ('<');
}

static char	parse_letters(char **s, char *es)
{
	while (*s < es && !ft_strchr(WHITESPACE, **s)
		&& !ft_strchr(TOKEN_DELIMS, **s))
		(*s) += 1;
	return ('a');
}

char	get_token(char **ps, char *es, char **t, char **et)
{
	char	*s;
	char	ret;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	if (t)
		*t = s;
	ret = *s;
	if (ret == 0)
		;
	else if (ret == '<')
		ret = parse_less_than(&s);
	else if (ret == '>')
		ret = parse_more_than(&s);
	else if (ret == '|' || ret == '$')
		s++;
	else
		ret = parse_letters(&s, es);
	if (et)
		*et = s;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	*ps = s;
	return (ret);
}
