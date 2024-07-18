/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:22:19 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/18 16:14:53 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //for printf
# include <readline/readline.h> // for rl library
# include <readline/history.h> // for rl history functionality
# include <errno.h> // for error handeling
# include <sys/wait.h> // for waiting for child processes
#include <dirent.h> // for accessing directories
# include "../libft/libft.h"
# include "./tree_builder.h"
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

# define PROMPT "THE FUCK DO YOU WANT?: "
# define LAUNCH_ERROR "Did you actually give arguments to launch a shell?\nWhat are you, some kind of idiot?\n"
# define FORK_ERROR "This fork mf decided to be a little bitch\n."
# define SYNTAX_ERROR "LMAOO YOU CANT EVEN WRITE PROPERLY GO LEARN SOME BASIC SYNTAX YOU DIPSHIT\n"

// characher sets for token delimitation
# define WHITESPACE " \t\r\n\v"
# define TOKEN_DELIMS " <>|$"

// Flags for input cleaning
# define F_OPEN_SINGLE 0
# define F_OPEN_DOUBLE 1
# define F_PIPE 2
# define F_SPACE 3

// Types of nodes
# define EXEC 0
# define REDIR 1
# define PIPE 2

//General struct that can be typecasted into any node type
typedef struct	s_cmd
{
	int	type;
}	t_cmd;

typedef struct	s_exec
{
	int	type;
	t_list	*argv;
	char	**envp;
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
	char **sort;
}	t_localenv;

extern int g_signo;

// helpers.c
int	is_fon(int flags, int f);
void	set_flag(int *flags, int f, bool set);

// exit.c
void	tokenizer_exit(char *line, t_tokenizer_data *td);

// free_tree.c
void	ft_free_tree(t_cmd *node);

// tokenlst_helpers.c
t_token *ft_tokennew(char type, char *content);
t_token *ft_tokenlast(t_token *token);
void    ft_tokenadd_back(t_token **token, t_token *new);
int	ft_token_createadd(t_token **tokenlst, char type, char *tokenstr);
void	ft_free_tokenlst(t_token *tokenlst, bool free_content);

// constructors.c
t_cmd	*exec_cmd(char **envp);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd	*redir_cmd(t_cmd *cmd, char *file, int mode, int fd);

//TOKENIZER.C
int	ft_expand_env(char **cmd, char **token, char **envp);
// Takes a pointer 'cmd', finds and expands the var pointed by it 
// and appends that expansion to 'token'.
// 'cmd' is updated to point at the first byte after the tested envvar.
// Returns 0 if successful. In case of error, 'token' is freed and returns 1 .
int	update_token(char **token, char *start, int size);
// Takes an existing 'token' and appends to it 'size' bytes of a strig pointed by 'start'.
// Returns 0 if successful. In case of error, 'token' is freed and set to NULL, and 1 is returned.
int	get_quoted(char **cmd, char **token, char **envp);
// Appends to 'token' the quoted string pointed by 'cmd' which starts with quote type 'c'.
// Returns 0 if successful, 1 if there is an error. If error comes from malloc, 'token' becomes NULL.
int	parse_spaces(t_tokenizer_data *td);
//Parses space present in cmd. Returns 0 on Success, 1 on Error.
t_token	*tokenizer(char *cmd, char **envp);

//TREE_BUILDER.C
t_cmd   *tree_builder(t_token *tokenlst, char **envp);

//TREE_EXECUTER.C
void	run_cmd(t_cmd *cmd, t_cmd *start);

//command_helpers.c
char	*validate_cmd(char *cmd, char **env);

// echo.c
void	echo(char **msg);
bool	find_n(char *str);

// export.c
int	ft_getenv(const char *name, char **value, char **envp);
// Searches for the envvar 'name' in 'envp' and saves its value in 'value'.
// Returns 1 if any error occured, 0 otherwise.
// 'value' is set to NULL in case of error or if 'name' was not found in 'envp'.
bool	isvar_valid(const char *name);
int	find_variable_index_recursive(const char *name, char **env, int i);

#endif
