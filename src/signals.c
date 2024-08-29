/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:54:09 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/17 18:41:44 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_signal_heredoc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_default(void)
{
	signal(SIGINT, signal_handler_default);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_pipeline(void)
{
	signal(SIGINT, signal_handler_pipeline);
	signal(SIGQUIT, SIG_IGN);
}
