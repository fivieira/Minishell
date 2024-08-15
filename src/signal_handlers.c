/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:56:03 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/02 16:10:26 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	setget_signo(int action, int ntoset)
{
	static int	g_signo = 0;

	if (action == SET)
		g_signo = ntoset;
	else if (action == GET)
		return (g_signo);
	return (0);
}

void	signal_handler_default(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		setget_signo(SET, SIGINT);
	}
}

void	signal_handler_pipeline(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		setget_signo(SET, SIGINT);
	}
}

void	signal_handler_pipeline_childs(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		setget_signo(SET, SIGINT);
	}
}


//TODO change sigquit to custom
