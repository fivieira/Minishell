/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:29:53 by fivieira          #+#    #+#             */
/*   Updated: 2024/06/27 12:49:11 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_echo(int ac, char *av[])
{
	bool	flag;
	
	flag = true;
	if (ac == 1)
		flag = false;
	while (av[ac])
	{
		printf("%s", av[ac]);
		if(av[ac + 1])
			printf(" ");
		ac++;	
	}
	if(!flag)
		printf("\n");
}

void	echo(t_exec * msg)
{
	
}

