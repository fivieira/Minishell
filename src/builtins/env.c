/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:21:07 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/18 22:14:19 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	command_env(t_localenv *local)
{
	if (local == NULL)
	{
		ft_putstr_fd(": local environment is NULL\n", 2);
		return (exit_code(EXIT_FAILURE));
	}	
	//prtstr_env(local->content);
	return (exit_code(EXIT_SUCCESS)); // tratar erro com os sinais
}
