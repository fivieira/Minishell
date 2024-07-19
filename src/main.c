/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:24:57 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/19 21:43:33 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_signo = 0;

void	close_temps(void);

/*
void	ft_heredoc(char *line)
{
	int	inquotes;

	inquotes = 0;
	while (*line)
	{
		if (!inquotes && *line == '<' && *(line + 1) == '<')
		{
			
		}
}*/


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
	cp_status = 0;
	while (1)
	{
		line = readline(PROMPT);
		if (!line)//Ctrl+D
		{
			ft_putstr_fd("exit\n", 1);
			exit(WEXITSTATUS(cp_status));
		}
//		ft_heredoc(line);







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
		ft_free_tree(tree);
                free(line);
		wait(&cp_status);
		close_temps();
		if (WIFEXITED(cp_status)) //exited normally
		{
			errno = WEXITSTATUS(cp_status);
			printf("%i\n", errno);
		}
		else
		{
			ft_printf("lol\n");// TODO: THIS ELSE HANDLES EXITING THROUGH SIGNALS
			 // UPDATE: Turns out this does not handle exiting though signals
			 // Maybe all this has to run in a different process, and 
			 // handle exiting in parent this way?
			break ;
		}
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
