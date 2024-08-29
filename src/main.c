/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:28:21 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/21 18:34:06 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_pipeline(t_root *r)
{
	pid_t	cpid;
	int		cpstatus;

	cpstatus = 0;
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
		else if (WIFSIGNALED(cpstatus) && WTERMSIG(cpstatus) == SIGINT)
			write(2, "\n", 1);
		r->exit_code = 128 + WTERMSIG(cpstatus);
	}
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
