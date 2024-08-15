/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:22:20 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/01 16:08:54 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char **argv, char ***envp)
{
	int	i;

	(void)argv;
	i = -1;
	if (!*envp)
		return (0);
	while ((*envp)[++i])
	{
		if (ft_strchr((*envp)[i], '='))
			ft_printf("%s\n", (*envp)[i]);
	}
	return (0);
}
