/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:24:57 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/24 21:37:01 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*parse_exec(

t_cmd	*parse_pipe(char *line)
{
	
}

t_cmd	*parse_line(

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
			return (ft_putstr_fd(FORK_ERROR, 2), errno);
		else if (cpid == 0)
			parse_pipe(line);
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
}
