/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:55:16 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/18 21:59:45 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_code(int code)
{
	if (code == 298)
	{
		g_signo = 42;
		return (g_signo);
	}
	if (code == 5120 || code == 13)
	{
		g_signo = 126;
		return(g_signo);
	}
	if (code == 512)
	{
		g_signo = 127;
		return (g_signo);
	}
	if(code >= 256 || code <= -256)
	{
		g_signo = WEXITSTATUS(code);
		return (g_signo);
	}
	else
		g_signo = code;
	return (g_signo);
}
