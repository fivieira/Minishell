/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:00:04 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/26 18:06:42 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_sig_function(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_sig_new(void)
{
	signal(SIGINT, SIG_DFL); //update_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	set_sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_sigint_status(void)
{
	signal(SIGINT, update_status_sigint);
	signal(SIGQUIT, update_status_sigquit);
}