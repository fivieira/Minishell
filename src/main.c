/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:24:57 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/17 15:35:36 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_temps(void);

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*organized;
	t_cmd	*tree;
	pid_t	cpid;
	int	cp_status;


	if (argc != 1)
		return (ft_putstr_fd(LAUNCH_ERROR, 2), 0);
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			continue ;
		organized = tokenizer(line, envp);
		if (!organized)
		{
			free(line);
			continue ;
		}
		tree = tree_builder(organized, envp);
		cpid = fork();
		if (cpid == -1)
			return (perror("fork"), errno);
		if (cpid == 0)
			run_cmd(tree, tree);
		wait(&cp_status);
		//There are still a few frees to do here!!
		/*free(((t_exec *)tree)->argv->content);
		free(((t_exec *)tree)->argv);
		free(tree);*/
		ft_free_tree(tree);
		free(line);
		close_temps();

		/*
		if (WIFEXITED(cp_status)) //exited normally
			errno = WEXITSTATUS(cp_status);
		else
		{
			ft_printf("lol\n");// TODO: THIS ELSE HANDLES EXITING THROUGH SIGNALS
			 // UPDATE: Turns out this does not handle exiting though signals
			 // Maybe all this has to run in a different process, and 
			 // handle exiting in parent this way?
			break ;
		}*/
	}
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
