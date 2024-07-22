/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:24:57 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/22 10:45:26 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_signo = 0;

void	close_temps(void);

void	get_line(t_root *r)
{
	r->line = readline(PROMPT);
	if (!r->line)
	{
		ft_putstr_fd(CTRLD_EXIT_MSG, 1);
		exit(WEXITSTATUS(r->cp_status));
	}
}

int	ft_readline_loop(t_root *r)
{
	get_line(r);
	if (!tokenizer(r))
		return (0);
	tree_builder(r);
	if (errno != 0) //in case errno was set by a signal?
		return (0);
	r->cpid = fork();
	if (r->cpid == -1)
		return (perror(FORK_ERROR), errno);
	if (r->cpid == 0)
		run_cmd(r->tree, r->tree);
	ft_free_tree(r->tree);
	free(r->line);
	wait(&r->cp_status);
	close_temps();
	if (WIFEXITED(r->cp_status))
		return (WEXITSTATUS(r->cp_status));
	else
	{
		ft_printf("lol\n");
		return (-1) ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_root	r;
	
	if (argc != 1)
		return (ft_putstr_fd(LAUNCH_ERROR, 2), 0);
	(void)argv;
	r.line = NULL;
	r.organized = NULL;
	r.tree = NULL;
	r.cp_status = 0;
	r.envp = envp;
	while (1)
		errno = ft_readline_loop(&r);
	return (errno);
}

void	close_temps(void)
{
	DIR	*tempdir;
	struct dirent	*file;
	char	*filename;
	
	tempdir = opendir(".tempfiles");
	if (!tempdir)
		exit(errno);
	file = readdir(tempdir);
	if (errno)
		exit(errno);
	while (file)
	{
		filename = ft_strjoin(".tempfiles/", file->d_name);
		if (!filename)
			exit(errno);
		if ((file->d_name)[0] != '.')
			unlink(filename);
		free(filename);
		file = readdir(tempdir);
		if (errno)
			exit(errno);
	}
	if (closedir(tempdir) != 0)
		exit(errno);
}
