/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:10:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/23 14:11:50 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char **argv, char** envp)
{
	(void)argv;
	(void)envp;
	free(argv);
	exit(errno); //TODO: send signal instead!! This way, the writing "exit" only shows up
			// if this command runs in the parent process.
}
