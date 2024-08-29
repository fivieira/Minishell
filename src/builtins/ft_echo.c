/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:10:48 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/18 15:17:33 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_n(char *arg)
{
	if (*arg != '-')
		return (0);
	arg += 1;
	if (!*arg)
		return (0);
	while (*arg)
	{
		if (*arg != 'n')
			return (0);
		arg += 1;
	}
	return (1);
}

int	ft_echo(char **argv, char ***envp)
{
	int		i;
	int		flag;

	(void)envp;
	i = 0;
	flag = 0;
	while (argv[++i] && is_n(argv[i]))
		flag = 1;
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (argv[i])
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
