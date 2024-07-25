/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:01:47 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/25 17:48:03 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_status_sigint(int signo)
{
	if(signo == SIGINT)
		g_signo = 130;
}

void	update_status_sigquit(int signo)
{
	if(signo == SIGQUIT)
		g_signo = 131;
}

void	sigint_handler(int signo)
{
	(void) signo;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_signo = 130;
		return ;
}

void	sigquit_handler(int signo)
{
	(void) signo;
	write(STDIN_FILENO, "\n", 1);
	g_signo = 131;
	return ;
}