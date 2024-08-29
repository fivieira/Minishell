/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:31:04 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/19 23:34:18 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_quotes(t_flags *f, char q)
{
	if (q == '\"' && !f->sq)
	{
		f->prev = EXEC;
		f->dq = (f->dq + 1) % 2;
	}
	else if (q == '\'' && !f->dq)
	{
		f->prev = EXEC;
		f->sq = (f->sq + 1) % 2;
	}
}

static void	handle_pipe(t_flags *f, char **ptr, int *exit_code)
{
	if (!(f->dq || f->sq))
	{
		if (f->prev == PIPE || f->prev == REDIR)
		{
			print_syntax_error(**ptr);
			*exit_code = SYNTAX_ERROR_CODE;
		}
		f->prev = PIPE;
	}
}

static void	handle_redirs(t_flags *f, char **ptr, int *exit_code)
{
	if (!(f->dq || f->sq))
	{
		if (f->prev == REDIR)
		{
			print_syntax_error(**ptr);
			*exit_code = SYNTAX_ERROR_CODE;
		}
		else if (**ptr == *(*ptr + 1))
			*ptr += 1;
		f->prev = REDIR;
	}
}

void	handle_syntax(char *ptr, int *exit_code)
{
	t_flags	f;

	init_flags(&f);
	while (*ptr)
	{
		if (ft_strchr(SPACES, *ptr))
			;
		else if (*ptr == '\"' || *ptr == '\'')
			handle_quotes(&f, *ptr);
		else if (*ptr == '>' || *ptr == '<')
			handle_redirs(&f, &ptr, exit_code);
		else if (*ptr == '|')
			handle_pipe(&f, &ptr, exit_code);
		else
			f.prev = EXEC;
		if (*exit_code)
			return ;
		ptr += 1;
	}
	if (f.prev != EXEC || f.sq || f.dq)
	{
		*exit_code = SYNTAX_ERROR_CODE;
		ft_putstr_fd(SYNTAX_ERROR_END, 2);
	}
}
