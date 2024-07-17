/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:39:07 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/17 17:22:50 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_args(t_list *argv)
{
	char	**args;
	int	i;

	args = (char **)ft_calloc(ft_lstsize(argv) + 1, sizeof(char *));
	i = 0;
	while (argv)
	{
		args[i] = (char *)argv->content;
		i++;
		argv = argv->next;
	}
	return args;
}

void	run_exec(t_exec *cmd, t_cmd *start)
{
	char	*cmd_path;
	char	**args;

	args = create_args(cmd->argv);
	if (!args)
	{
		ft_free_tree(start);
		exit(errno);
	}
	cmd_path = validate_cmd(args[0], cmd->envp);
	if (!cmd_path)
	{
		ft_free_tree(start);
		free(args);
		exit(errno);
	}
	execve(cmd_path, args, cmd->envp);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(cmd_path);
	ft_free_tree(start);
	free(args);
	exit(127);
}

void	run_redir(t_redir *cmd, t_cmd *start)
{
	int	fd;

	fd = open(cmd->file, cmd->mode, 0644);
	dup2(fd, cmd->fd);
	close(fd);
	run_cmd(cmd->cmd, start);
}

void	run_pipe(t_pipe *cmd, t_cmd *start)
{
	int	p[2];

	if (pipe(p) < 0)
		return ; //TODO: DEAL WITH PIPE ERROR.
	if (fork() == 0)
	{
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		run_cmd(cmd->left, start);
	}
	if (fork() == 0)
	{
		dup2(p[0], 0);
		close(p[0]);
		close(p[1]);
		run_cmd(cmd->right, start);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
	ft_free_tree(start);
	exit(0);
}

void	run_cmd(t_cmd *cmd, t_cmd *start)
{
	if (cmd->type == PIPE)
		run_pipe((t_pipe *)cmd, start);
	else if (cmd->type == REDIR)
		run_redir((t_redir *)cmd, start);
	else if (cmd->type == EXEC)
		run_exec((t_exec *)cmd, start);
}
