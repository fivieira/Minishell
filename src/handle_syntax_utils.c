/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:07:40 by fivieira          #+#    #+#             */
/*   Updated: 2024/08/19 23:34:25 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_flags(t_flags *f)
{
	f->sq = 0;
	f->dq = 0;
	f->prev = PIPE;
}

void	print_syntax_error(char c)
{
	ft_putstr_fd(SYNTAX_ERROR, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\'\n", 2);
}
