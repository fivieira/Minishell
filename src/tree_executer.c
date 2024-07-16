/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:39:07 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/15 16:53:56 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_args(t_list *argv)
{
	char	**args;
	int	i;

	args = (char **)ft_calloc(ft_lstsize(argv), sizeof(char *));
	i = 0;
	while (argv)
	{
		args[i] = (char *)argv->content;
		i++;
		argv = argv->next;
	}
	return args;
}

void	run_exec(t_exec *cmd)
{
	char	*cmd_path;
	char	**args;

	args = create_args(cmd->argv);
	cmd_path = validate_cmd(args[0], cmd->envp);
	execve(cmd_path, args, cmd->envp);
	exit(errno);
}

void	run_redir(t_redir *cmd)
{
	int	fd;

	fd = open(cmd->file, cmd->mode, 0644);
	dup2(fd, cmd->fd);
	close(fd);
	run_cmd(cmd->cmd);
}

void	run_pipe(t_pipe *cmd)
{
	int	p[2];

	if (pipe(p) < 0)
		return ; //TODO: DEAL WITH PIPE ERROR.
	if (fork() == 0)
	{
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		run_cmd(cmd->left);
	}
	if (fork() == 0)
	{
		dup2(p[0], 0);
		close(p[0]);
		close(p[1]);
		run_cmd(cmd->right);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
	exit(0);
}

void	run_cmd(t_cmd *cmd)
{
	if (cmd->type == PIPE)
		run_pipe((t_pipe *)cmd);
	else if (cmd->type == REDIR)
		run_redir((t_redir *)cmd);
	else if (cmd->type == EXEC)
		run_exec((t_exec *)cmd);
}
