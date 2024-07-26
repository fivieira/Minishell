/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:22:19 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/26 19:25:27 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //for printf
# include <readline/readline.h> // for rl library
# include <readline/history.h> // for rl history functionality
# include <errno.h> // for error handeling
# include <sys/wait.h> // for waiting for child processes
# include <dirent.h> // for accessing directories
# include "../libft/libft.h"
# include "./tree_builder.h"
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

# define PROMPT "REPLACE WITH CURRENT WORKING DIR: "
# define LAUNCH_ERROR "Launch error\n"
# define CTRLD_EXIT_MSG "exit\n"
# define CTRLD_HEREDOC_MSG "warning: here-document delimited by end-of-file\n"
# define FORK_ERROR "fork\n"
# define SYNTAX_ERROR "Syntax error\n"

# define BUILTINS_AM 3

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

extern int g_signo;

typedef int (*builtin_ptr)(char **, char **);

//General struct that can be typecasted into any node type
typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_exec
{
	int		type;
	t_list	*argv;
	char	**envp;
}	t_exec;

typedef struct s_redir
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	char	redir_type;
	int		mode;
	int		fd;
}	t_redir;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

typedef struct s_localenv
{
	char	**content;
	char	**sort;
}	t_localenv;

typedef struct s_root
{
	char	*line;
	char	**envp;
	t_token	*organized;
	t_cmd	*tree;
	pid_t	cpid;
	int		cp_status;
}	t_root;

// EXIT.C
int   exit_code(int code);
void	tokenizer_exit(char *line, t_tokenizer_data *td);
// Cleanly frees the provided 'line' and all tokenizer_data and exits. 
void	tree_builder_exit(t_root *r, int exit_code, char *error_msg);
// Cleanly frees all data present in 'r', prints the error message
// according to errno if error_msg is not NULL and exits with 'exit_code'.

// FREE_TREE.C
void	ft_free_tree(t_cmd *node);
// Cleanly frees all data present in the tree with the head 'node'.

// tokenlst_helpers.c
t_token	*ft_tokennew(char type, char *content);
t_token	*ft_tokenlast(t_token *token);
void	ft_tokenadd_back(t_token **token, t_token *new);
int		ft_token_createadd(t_token **tokenlst, char type, char *tokenstr);
void	ft_free_tokenlst(t_token *tokenlst, bool free_content);

// CPNSTRUCTORS.C
t_cmd	*exec_cmd(char **envp);
// Builds an exec node and returns it as t_cmd (or NULL in case of error).
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
// Builds a pipe node and returns it as t_cmd (or NULL in case of error).
t_cmd	*redir_cmd(t_cmd *cmd, char *file, int mode, int fd);
// Receives a cmd which is a linked list of redir nodes
// finished by an exec node.
// Builds a new redir node and places it between
// the last redir and the exec nodes.
// Returns the HEAD of the list (or NULL in case of error).

//TOKENIZER.C
int		update_token(char **token, char *start, int size);
// Takes an existing 'token' and appends to it 'size' bytes 
// of a strig pointed by 'start'.
// Returns 0 if successful. In case of error, 'token' is freed 
// and set to NULL, and 1 is returned.
int		get_quoted(char **cmd, char **token, t_root *);
// Appends to 'token' the quoted string pointed by 'cmd'
// which starts with quote type 'c'.
// Returns 0 if successful, 1 if there is an error. 
// If error comes from malloc, 'token' becomes NULL.
int		parse_spaces(t_tokenizer_data *td);
//Parses space present in cmd. Returns 0 on Success, 1 on Error.
t_token	*tokenizer(t_root *r);

// tokenizer_helpers.c
int		parse_spaces(t_tokenizer_data *td);
void	parse_redirs(t_tokenizer_data *td);
int		parse_redirs_pipes(t_tokenizer_data *td);

// TREE_BUILDER.C
int	tree_builder(t_root *r);

// HEREDOC.C
int		set_heredocs(t_cmd *cmd, t_root *r, int *status);
// Creates all heredocs present in the tree 'cmd', 

// TREE_EXECUTER.C
void	run_cmd(t_cmd *cmd, t_cmd *start);
void	run_redir(t_redir *cmd, t_cmd *start);
char    **create_args(t_list *argv, bool);

// tree_helpers.c
int		get_next_rn(void);

//command_helpers.c
char	*validate_cmd(char *cmd, char **env);
// Tries to find the given 'cmd' in the provided path present in 'env'.
// Returns the path to the command binary if the command could be found.
// Returns the allocated str "INVALID" if the command could not be found.
// Returns NULL if there were any errors (with errno set).

// exec_builtins.c
int    find_exec_builtin(char **args, char **envp, t_cmd *tree);
void    builtin_redir(t_redir *cmd, t_cmd *start);
int	exec_parent_builtin(t_cmd *tree);

// builtins_utils.c
bool	is_end_cmd_builtin(t_cmd *tree);
int	get_builtin_func_i(char *cmd);
builtin_ptr	get_builtin(int i);

// ft_echo.c
int	ft_echo(char **msg, char **envp);

// ft_pwd.c
int	ft_pwd(char **argv, char **envp);

// ft_exit.c
int	ft_exit(char **argv, char **envp);

// export.c
int		ft_getenv(const char *name, char **value, char **envp);
// Searches for the envvar 'name' in 'envp' and saves its value in 'value'.
// Returns 1 if any error occured, 0 otherwise.
// 'value' is set to NULL in case of error or if 'name' was not found in 'envp'.
int		ft_expand_env(char **cmd, char **token, t_root *r);
// Takes a pointer to the '$' character of a string searches for the 
// subconsequent var in 'envp' and updates 'token' accordingly.
// 'cmd' is updated to point at the charecter 
// after the last one from the searched var.
// Returns 0 if successful (which includes the case where 
// the var was not found, in which case 'token' is left as is).
// Returns an error number otherwise.
bool	isvar_valid(const char *name);
int		find_variable_index_recursive(const char *name, char **env, int i);

//signals
void	sigint_handler(int signo);
void	update_status_sigint(int signo);
void	update_status_sigquit(int signo);
void	sigint_handler(int signo);
void	sigquit_handler(int signo);
void	handle_sigint_status(void);
void	set_sig_default(void);
void	set_sig_new(void);
void	set_sig_function(void);



//TEST
void	update_heredoc_sigint(int signo);
void	psigint_handler_hd(int signo);
#endif
