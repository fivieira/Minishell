/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 23:23:13 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/19 23:38:59 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_build_error_msg(char *origin, char *msg)
{
	char	*final_msg;

	final_msg = ft_strjoin(origin, msg);
	return (final_msg);
}

int	ft_print_buffered_error(char *msg)
{
	int	buff_fd;

	buff_fd = dup(STDOUT_FILENO);
	if (buff_fd < 0)
		return (perror("dup"), -1);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) < 0)
		return (perror("dup"), -1);
	printf("%s\n", msg);
	if (dup2(STDOUT_FILENO, buff_fd) < 0)
		return (perror("dup"), -1);
	close(buff_fd);
	return (0);
}

int	ft_print_error(char *msg)
{
	int	status;

	status = 0;
	if (errno)
		perror(msg);
	else
		status = ft_print_buffered_error(msg);
	return (status);
}
