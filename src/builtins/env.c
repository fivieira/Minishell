/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:21:07 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/18 12:52:11 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	command_env(t_localenv *local)
{
	if (local == NULL)
		return (1); // tratar erro com os sinais
	//prtstr_env(local->content);
	return (0); // tratar erro com os sinais
}
