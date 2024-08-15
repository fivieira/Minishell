/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:25:08 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/13 12:46:06 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/heredoc.h"

static int	save_envp(char **envp)
{
	int		fd;
	int		i;
	char	*envp_filename;

	envp_filename = ft_strjoin(get_tempfiles_folder(), ENVP_FILENAME);
	if (!envp_filename)
		return (1);
	fd = open(envp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(envp_filename);
	if (fd < 0)
		return (1);
	i = -1;
	while (envp[++i])
	{
		write(fd, envp[i], ft_strlen(envp[i]));
		write(fd, "\n", 1);
	}
	close(fd);
	return (0);
}

static void	child(char *eof, char *filename, t_root *r, char hd_type)
{
	init_tempfiles_path(r->tempfiles_dir);
	eof = ft_strdup(eof);
	free_tree(&r->tree);
	if (!eof)
	{
		perror("malloc");
		free_exit(r, errno);
	}
	set_signal_heredoc();
	if (save_envp(r->envp) != 0)
	{
		perror("envp save");
		free_exit(r, errno);
	}
	ft_matrix_free((void ***)&r->envp);
	create_heredoc_file(filename, eof, hd_type);
}

static char	*handle_heredoc_result(int cp_status, char *filename, t_root *r)
{
	set_signal_default();
	if (WIFEXITED(cp_status))
	{
		if (WEXITSTATUS(cp_status) == 0)
			return (filename);
		else
		{
			free(filename);
			r->exit_code = WEXITSTATUS(cp_status);
			return (NULL);
		}
	}
	else
	{
		free(filename);
		write(1, "\n", 1);
		if (WTERMSIG(cp_status) == SIGINT)
			r->exit_code = 130;
	}
	return (NULL);
}

char	*heredoc(char *eof, t_root *r, char hd_type)
{
	char	*filename;
	pid_t	cpid;
	int		cp_status;

	filename = ft_strjoin_free(ft_strdup(r->tempfiles_dir),
			ft_strjoin_free(ft_strdup("tempheredoc"),
				ft_itoa(get_next_rn())));
	if (!filename)
		return (NULL);
	cpid = fork();
	if (cpid == -1)
		return (free(filename), NULL);
	else if (cpid == 0)
		child(eof, filename, r, hd_type);
	free(eof);
	signal(SIGINT, SIG_IGN);
	wait(&cp_status);
	return (handle_heredoc_result(cp_status, filename, r));
}
