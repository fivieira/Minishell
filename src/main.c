/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:24:57 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/18 21:36:35 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_signo = 0;

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
		{
			ft_putstr_fd("exit\n", 1);
			exit(cp_status); //TODO: Exiting with Ctr+d is not currently giving right exit
		}
		//TODO: EXPAND MUST BE DONE BEFORE TOKENIZER BECAUSE QUOTE RULES STILL APPLY
		// BUT SOMEHOW NOT BE INTERPRETED AS TOKENS??
		// export VAR="intf abc |"
		// pr$VAR executes command WITHOUT syntax error ('|' is treated as str and not token)
		// pr"$VAR" does not execute, because command "printf abc |" does not exist
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
		wait(&cp_status); //TODO: Check if exit through signals is giving right exit
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
