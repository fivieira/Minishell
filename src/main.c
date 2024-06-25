/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:24:57 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/25 16:44:24 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	peek(char **ps, char *chars)
{
	char	*s;

	s = *ps;
	while (*s && ft_strchr(WHITESPACE, *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(chars, *s));
}

t_cmd	*parse_redir(t_cmd *cmd, char **ps)
{
	char	token;
	char	*file_pos;

	while (peek(ps, "<>"))
	{
		token = get_token(ps, 0);
		if (get_token(ps, &file_pos) != 'a')
			return (NULL); //TODO: How to inform about syntax error??
		if (token == '<')
			cmd = redir_cmd(cmd, file_pos, O_RDONLY, 0);
		else if (token == '-')
			;//TODO: IMPLEMENT HEREDOC
		else if (token == '>')
			cmd = redir_cmd(cmd, file_pos, O_WRONLY|O_CREATE|O_TRUNC, 1);
		else if (token == '+')
			cmd = redir_cmd(cmd, file_pos, O_WRONLY|O_CREATE|O_APPEND, 1); 
	}
	return (cmd);
}

t_cmd	*parse_exec(char **ps)
{
	t_cmd	*node;
	t_exec	*full_node;
	char	token;
	char	*arg_pos;
	int	argc;

	node = exec_cmd();
	full_node = (t_exec *)node;
	node = parse_redir(node, ps);
	argc = 0
	while(!peek(ps, "|"))
	{
		token = get_token(ps, &arg_pos);
		if (token == 0)
			break ;
		if (token != 'a')
			return (NULL) //TODO: How to inform about syntax error??
		full_node->argv[argc] = arg_pos; //TODO: IMPORTANT!!!!!
						 //Memory for this has to be allocated
						 //at some point. How to make it dynamic
						 //so it can accept any number of arguments???
		argc++;
		node = parse_redir(node, ps);
	}
	full_node->argv[argc] = NULL;
	return (node);
}

t_cmd	*parse_pipe(char **ps)
{
	t_cmd	*node;

	node = parse_exec(ps);
	if (get_token(ps, 0, 0) == "|")
		node = pipe_cmd(node, parse_pipe(ps));
	return (node);
}

void	parse_line(char *line)
{
	t_cmd	*tree;
	char	*ps;

	ps = line;
	tree = parse_pipe(&ps);
}

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
}
