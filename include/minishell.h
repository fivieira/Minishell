/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:22:19 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/02 15:19:51 by ndo-vale         ###   ########.fr       */
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

# define PROMPT "THE FUCK DO YOU WANT?: "
# define LAUNCH_ERROR "Did you actually give arguments to launch a shell?\nWhat are you, some kind of idiot?\n"
# define FORK_ERROR "This fork mf decided to be a little bitch."

// characher sets for token delimitation
# define WHITESPACE " \t\r\n\v"
# define TOKEN_DELIMS " <>|$"

// Flags for input cleaning
# define F_OPEN_SINGLE 0
# define F_OPEN_DOUBLE 1
# define F_PIPE 2
# define F_SPACE 3

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
	t_cmd	*cmd;
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

typedef struct s_localenv
{
	char **content;
}	t_localenv;

// helpers.c
int	is_fon(int flags, int f);
void	set_flag(int *flags, int f, bool set);

// constructors.c
t_cmd	*exec_cmd(void);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd	*redir_cmd(t_cmd *cmd, char *file, int mode, int fd);

char	get_token(char **ps, char **t);
char	*clean_input(char *cmd, char **envp);

// echo.c
void	echo(char **msg);
bool	find_n(char *str);

char	*ft_getenv(const char *name, char **envp);

#endif
