/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:22:19 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/28 11:15:42 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //for printf
# include <readline/readline.h> // for rl library
# include <readline/history.h> // for rl history functionality
# include <errno.h> // for error handeling
# include <sys/wait.h> // for waiting for child processes
# include "../libft/libft.h"
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

# define PROMPT "WRITE SOMETHING, BITCH: "
# define LAUNCH_ERROR "Did you actually give arguments to launch a shell?\nWhat are you, some kind of idiot?\n"
# define FORK_ERROR "This fork mf decided to be a little bitch."

// characher sets for token delimitation
# define WHITESPACE " \t\r\n\v"
# define TOKEN_DELIMS " <>|$"

// Types of nodes
# define EXEC 1
# define REDIR 2
# define PIPE 3

//General struct that can be typecasted into any node type
typedef struct	s_cmd
{
	int	type;
}	t_cmd;

typedef struct	s_exec
{
	int	type;
	t_list	*argv;
}	t_exec;

typedef struct	s_redir
{
	int	type;
	t_exec	*cmd;
	char	*file;
	int	mode;
	int	fd;
}	t_redir;

typedef struct	s_pipe
{
	int	type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

// Constructors
t_cmd	*exec_cmd(void);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd	*redir_cmd(t_exec *cmd, char *file, int mode, int fd);

char	get_token(char **ps, char **t);


// echo.c
void	echo(char **msg);
bool	find_n(char *str);

#endif
