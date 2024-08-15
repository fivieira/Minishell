/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:21:46 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/01 16:11:54 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(char **argv, char ***envp)
{
	int	i;

	i = 0;
	while (argv[++i])
		delete_var(argv[i], *envp);
	return (0);
}
