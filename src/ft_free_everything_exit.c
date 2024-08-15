/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_everything_exit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:55:37 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/10 14:05:02 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_build_error_msg(char *origin, char *msg)
{
	char *final_msg;

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

void	exit_with_standard_error(t_root *r, char *msg, int exit_code, int allocated)
{
	ft_print_error(msg);
	if (allocated)
		free(msg);
	free_everything_exit(r, exit_code);
}

void    exit_with_custom_error(t_root *r, char *origin, char *msg, int exit_code)
{
	char	*error_msg;

	error_msg = ft_build_error_msg(origin, msg);
	free(origin);
    ft_print_error(error_msg);
	free(error_msg);
    free_everything_exit(r, exit_code);
}

void	free_root(t_root *r)
{
	free(r->line);
	r->line = NULL;
	free(r->stoken);
	r->stoken = NULL;
    ft_matrix_free((void ***)&r->envp);
    free_tokenlst(&r->token_lst);
    free_tree(&r->tree);
}

void    free_everything_exit(t_root *r, int exit_code)
{
    free(r->line);
	r->line = NULL;
	free(r->stoken);
	r->stoken = NULL;
    ft_matrix_free((void ***)&r->envp);
    free_tokenlst(&r->token_lst);
    free_tree(&r->tree);
    exit(exit_code);
}