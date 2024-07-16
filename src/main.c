/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:24:57 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/16 15:34:50 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//----------------------------------------//
//THE BELOW CODE IS THE ORIGINAL MAIN. UNCOMMENT THIS WHEN NO MORE NEED FOR TEST MAIN
//----------------------------------------//
/*
int	main(int argc, char **argv, char **envp)
{
	char	*line;
	pid_t	cpid;
	int	cp_status;


	if (argc != 1)
		return (ft_putstr_fd(LAUNCH_ERROR, 2), 0);
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline(PROMPT);
		cpid = fork();
		if (cpid == -1)
			return (perror("fork"), errno);
		//else if (cpid == 0)
		//	parse_pipe(line);
		wait(&cp_status);
		if (WIFEXITED(cp_status)) //exited normally
			errno = WEXITSTATUS(cp_status);
		else
		{
			// TODO: THIS ELSE HANDLES EXITING THROUGH SIGNALS
		}
		free(line);
	}
	return (errno);
}*/

void	close_temps(void)
{
	DIR	*tempdir;
	struct dirent	*file;
	
	tempdir = opendir(".tempfiles");
	file = readdir(tempdir);
	while (file)
	{
		if ((file->d_name)[0] != '.')
			unlink(ft_strjoin(".tempfiles/", file->d_name));
		file = readdir(tempdir);
	}
	closedir(tempdir);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*organized;


	if (argc != 1)
                return (ft_putstr_fd(LAUNCH_ERROR, 2), 0);
	(void)argv;
	while (1)
	{
		line = readline(PROMPT);
		organized = tokenizer(line, envp);
		if (!organized)
		{
			free(organized);
			continue ;
		}
		t_cmd	*tree = tree_builder(organized, envp);
		if (fork() == 0)
		{
			run_cmd(tree);
			exit(0);
		}
		wait(0);
		close_temps();
	}
}
