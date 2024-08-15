/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:28:21 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/13 20:15:45 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_pipeline(t_root *r)
{
	pid_t	cpid;
	int		cpstatus;

	cpid = fork();
	if (cpid == -1)
		exit_with_standard_error(r, "fork", errno, 0);
	if (cpid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, signal_handler_pipeline_childs);
		execute_node(r->tree, r);
	}
	free_tree(&r->tree);
	wait(&cpstatus);
	if (WIFEXITED(cpstatus))
		r->exit_code = WEXITSTATUS(cpstatus);
	else
	{
		if (WCOREDUMP(cpstatus))
			ft_putstr_fd(CORE_DUMP_MSG, STDERR_FILENO);
		r->exit_code = 128 + WTERMSIG(cpstatus);
	}
}

static void	execute_builtin_in_parent(t_root *r)
{
	t_exec	*exec_node;
	int		original_stdout;
	int		original_stdin;
	
	exec_node = (t_exec *)r->tree;
	original_stdin = dup(STDIN_FILENO); //Protect
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdout < 0)
	{
		perror("dup");
		free_tree(&r->tree);
		return ;
	}
	if (execute_redirs(exec_node->redirs, r) != 0)
	{
		close(original_stdout);
		free_tree(&r->tree);
		return ;
	}
	if (ft_strncmp(exec_node->argv->content, "exit", 5) == 0)
		ft_exit_parent(r, exec_node);
	else
		r->exit_code = run_builtin(((t_exec *)r->tree)->argv, &r->envp);
	if (errno)
		exit_with_standard_error(r, "builtin", errno, 0);
	free_tree(&r->tree);
	if (dup2(original_stdout, STDOUT_FILENO) < 0)
		perror("dup");
	dup2(original_stdin, STDIN_FILENO); //Protect
	close(original_stdout);
}

static void	ft_readline_loop(t_root *r)
{
	if (get_line(r) != 0)
		return ;
	add_history(r->line);
	handle_syntax(r->line, &r->exit_code);
	if (r->exit_code)
		return ;
	tokenize_line(r);
	if (r->exit_code != 0 || !r->token_lst)
		return ;
	if (build_tree(r) != 0)
		return ;
	if (r->tree->type == EXEC && ((t_exec *)r->tree)->argv
		&& get_builtin(((t_exec *)r->tree)->argv->content))
		execute_builtin_in_parent(r);
	else
	{
		set_signal_pipeline();
		run_pipeline(r);
		set_signal_default();
	}
}

static void	init_root(t_root *r, char **envp)
{
	r->line = NULL;
	r->envp = (char **)ft_matrix_dup((void **)envp);
	if (!r->envp)
	{
		perror("malloc");
		exit(errno);
	}
	getcwd(r->tempfiles_dir, BUFFER_MAX_SIZE);
	if (errno)
	{
		perror("getcwd");
		ft_matrix_free((void ***)envp);
		exit(errno);
	}
	ft_strlcat(r->tempfiles_dir, TEMPFILES_DIR, BUFFER_MAX_SIZE);
	r->token_lst = NULL;
	r->tree = NULL;
	r->stoken = NULL;
	r->exit_code = 0;
	r->prev_exit_code = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_root	r;
	
	if (argc != 1)
		return (ft_putstr_fd(LAUNCH_ERROR, STDERR_FILENO), 0);
	(void)argv;
	init_root(&r, envp);
	set_signal_default();
	while (1)
	{
		errno = 0;
		ft_readline_loop(&r);
		free(r.line);
		if (close_temps(r.tempfiles_dir) != 0)
		{
			perror("close temps");
			free_exit(&r, errno);
		}
	}
	return (0);
}
