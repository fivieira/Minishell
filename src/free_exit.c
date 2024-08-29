/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:22:59 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/19 23:32:37 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	close_temps(char *tempfiles_dir)
{
	DIR				*tempdir;
	struct dirent	*file;
	char			*filename;

	tempdir = opendir(tempfiles_dir);
	if (!tempdir)
		return (errno);
	errno = 0;
	file = readdir(tempdir);
	if (errno)
		return (errno);
	while (file)
	{
		filename = ft_strjoin(tempfiles_dir, file->d_name);
		if (!filename)
			return (errno);
		if ((file->d_name)[0] != '.')
			unlink(filename);
		free(filename);
		errno = 0;
		file = readdir(tempdir);
		if (errno)
			return (errno);
	}
	return (closedir(tempdir), errno);
}

void	free_exit(t_root *r, int exit_code)
{
	ft_matrix_free((void ***)&r->envp);
	rl_clear_history();
	exit(exit_code);
}

void	clean_exit_minishell(t_root *r, int exit_code)
{
	ft_putstr_fd("exit", 2);
	free_exit(r, exit_code);
}

void	exit_in_init(char *reason, t_root *r)
{
	perror(reason);
	if (r->envp)
		ft_matrix_free((void ***)&r->envp);
	exit (errno);
}
