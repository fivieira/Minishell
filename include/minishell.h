/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:30:43 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/14 21:03:46 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include <readline/readline.h> // readline
# include <readline/history.h>
# include <errno.h> // error codes
# include <signal.h> // signals
# include <sys/wait.h> // wait for child process
# include <fcntl.h> // file manipulation
# include <dirent.h> // folder manipulation
# include "../libft/libft.h" // libft

// MESSAGES
# define LAUNCH_ERROR "minishell does not accept extra options. \
Please launch it without arguments.\n"
# define TEMPFILES_DIR "/.tempfiles/"
# define PROMPT "Enter your command: "
# define CTRD_EXIT_MSG "exit\n"
# define SYNTAX_ERROR "syntax error near unexpected token `"
# define SYNTAX_ERROR_END "syntax error near unexpected token `newline'\n"
# define CORE_DUMP_MSG "Quit (core dumped)\n"
# define CMD_NOT_FOUND_MSG ": command not found"
# define PERMISSION_DENIED_MSG ": permission denied"

// CODES
# define CTRLC_SIGNO 2
# define SYNTAX_ERROR_CODE 2

// TYPES OF NODES
# define REDIR 0
# define EXEC 1
# define PIPE 2

// MISCELLANEOUS DEFINES
# define BUFFER_MAX_SIZE 1024
# define SPACES " \t\n\v\f\r"
# define TOKEN_CHARS "<>|"
# define REDIR_TYPES "<>+-_"
# define SET 0
# define GET 1
# define BUILTINS_AM 7
# define ENVP_FILENAME "/env_filename_because_we_gotta_find_the\
_dumbest_ways_to_get_around_this_damn_subject"






//TEST
void	signal_handler_pipeline_childs(int signo);




// STRUCTS
// Syntax handler
typedef struct s_flags
{
	int	sq;
	int	dq;
	int	prev;
}	t_flags;

// Tokenizer
typedef struct s_token
{
	char			type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_tokenizer_data
{
	//t_token	*token_lst;
	char	*ptr;
	char	type;
	//char	*stoken;
	int		status;
}	t_tokenizer_data;

// Tree builder
typedef struct s_node
{
	int	type;
}	t_node;

typedef struct s_redir
{
	int				type;
	char			*file;
	char			redir_type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_exec
{
	int		type;
	t_list	*argv;
	t_redir	*redirs;
}	t_exec;

typedef struct s_pipe
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_pipe;

// Root struct
typedef struct s_root
{
	char		*line;
	char		**envp;
	char		*stoken;
	t_token		*token_lst;
	t_node		*tree;
	int			exit_code;
	int			prev_exit_code;
	char		tempfiles_dir[BUFFER_MAX_SIZE];
}	t_root;

typedef int	(*t_builtin)(char **, char ***);

// FREE_EVERYTHING_EXIT.C
void    free_everything_exit(t_root *r, int exit_code);
void	exit_with_standard_error(t_root *r, char *msg, int exit_code, int allocated);
void    exit_with_custom_error(t_root *r, char *origin, char *msg, int exit_code);
void	free_root(t_root *r);
//Returns if func was successful.
int		ft_print_error(char *msg);
char	*ft_build_error_msg(char *origin, char *msg);

// MAIN_HELPERS.C
int			get_line(t_root *r);

// FREE_EXIT.C
//void		exit_from_te(t_root *r, char *msg, int exit_code);
void		free_exit(t_root *r, int exit_code);
int			close_temps(char *tempfiles_dir);

// SIGNALS.C
void		signal_handler_default(int signo);
void		signal_handler_pipeline(int signo);
void		set_signal_heredoc(void);
void		set_signal_default(void);
void		set_signal_pipeline(void);
int			setget_signo(int action, int ntoset);

// HANDLE_SYNTAX.C
void			handle_syntax(char *ptr, int *exit_code);

// HANDLE_SYNTAX_UTILS.C
void		init_flags(t_flags *f);
void		print_syntax_error(char c);

// TOKENIZE_LINE.C
void		tokenize_line(t_root *r);

// TOKENIZE_LINE2.C
int			update_token(char **token, char *start);
int			tokenize_env(t_root *r, t_tokenizer_data *td, char *env_value);
char		*expand_cmd_env(t_tokenizer_data *td, t_root *r);

// TOKENIZER_PARSERS.C
void		parse_quotes(t_tokenizer_data *td, t_root *r, char c);
void		parse_redirs_pipes(t_tokenizer_data *td, t_root *r);
void		parse_spaces(t_tokenizer_data *td, t_root *r);

// TOKENIZER_EXIT_FREE.C
//void		free_tokenizer(t_tokenizer_data *td);
//void		exit_from_tokenizer(t_tokenizer_data *td, t_root *r,
//				char *msg, int exit_code);

// GET_ENV_VALUE.C
int			get_env_key_len(char *start);
char		*get_env_key(char *start);
char		*get_env_value(char *start, char **envp);
void		update_env(char *name, char *value, char ***envp);

// TOKENLST_HELPERS.C
t_token		*tokennew(char type, char *content);
t_token		*tokenlast(t_token *token);
void		tokenadd_back(t_token **token, t_token *new);
int			token_createadd(t_token **tokenlst, char type, char *tokenstr);
void		free_tokenlst(t_token **tokenlst);

// BUILD_TREE.C
int			build_tree(t_root *r);

// NODE_CONSTRUCTORS.C
t_redir		*create_redir(char *file, char redir_type);
t_exec		*create_exec(void);
t_pipe		*create_pipe(t_node *left, t_node *right);

// SET_HEREDOCS.C
int			set_heredocs(t_node *node, t_root *r);

// HEREDOC.C
char		*heredoc(char *eof, t_root *r, char hd_type);

// HEREDOC_HELPERS.C
int			get_next_rn(void);
char		*find_and_expand(char *line);

// CREATE_HEREDOC_FILE.C
void		create_heredoc_file(char *filename, char *eof, char hd_type);

// GET_ENV_VALUE_HD.C
char		*get_env_value_hd(char *start);
int			create_envp_file(void);

// FREE_TREE.C
void		free_tree(t_node **tree);

// EXECUTE_NODE.C
char		**create_args(t_list *argv);
int			execute_redirs(t_redir *node, t_root *r);
void		execute_node(t_node *node, t_root *r);
void		apply_pipe_and_execute(t_node *node, t_root *r, int *p,
			int multipurp_fd);
void		failed_execve_aftermath(char *cmd_path, char **args, t_root *r);

//EXECUTE_NODE_HELPERS.C
int			get_redir_mode(char type);
int			get_redir_fd(char type);
void		close_pipe(int *p);
void		close_pipe_and_exit(int *p, t_root *r, char *msg);
void		try_running_builtin(t_exec *node, t_root *r);

// COMMAND_HELPERS.C
char		*validate_cmd(char *cmd, char **env);
char		**create_args(t_list *argv);

// BUILTIN_UTILS.C
int			run_builtin(t_list *argv_lst, char ***envp);
t_builtin	get_builtin(char *cmd);
void		delete_var(char *var, char **envp);
int			get_envp_i(char *key, char **envp);
int			is_key_valid(char *key);
//int			verify_getcwd(char *cwd, size_t size);
//int			verify_change_dir(char *dir);
int			count_envs(char **envp);
int			fill_new_envp(char **new, char ***old_ref);

// BUILTINS
int			ft_echo(char **argv, char ***envp);
int			ft_cd(char **argv, char ***envp);
int			ft_pwd(char **argv, char ***envp);
int			ft_export(char **argv, char ***envp);
int			ft_unset(char **argv, char ***envp);
int			ft_env(char **argv, char ***envp);
int			ft_exit(char **argv, char ***envp);
void		ft_exit_parent(t_root *r, t_exec *node);
void		ft_exit_pipeline(t_root *r, t_exec *node);

// export
void set_env_var(char *key, char *value, char **envp);
#endif
