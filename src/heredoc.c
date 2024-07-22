/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:16:46 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/22 15:58:03 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_and_expand(char **line, char **envp)
{
	char	*final;
	char	*ptr;
	int		status;

	ptr = *line;
	final = ft_strdup("");
	while (*ptr)
	{
		if (*ptr == '$')
			status = ft_expand_env(&ptr, &final, envp);
		else
		{
			status = update_token(&final, ptr, 1);
			ptr += 1;
		}
		if (status != 0)
			return (free(final), free(line), errno);
	}
	free(*line);
	*line = final;
	return (0);
}

char	*create_heredoc_file(char *filename, char *eof_str, char **envp)
{
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(filename);
	line = readline(">");
	while (line && ft_strncmp(line, eof_str, ft_strlen(eof_str) + 1) != 0)
	{
		if (find_and_expand(&line, envp) != 0)
			exit (errno);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(eof_str);
	free(line);
	close(fd);
	exit(0);
}

char	*heredoc(char *eof_str, t_cmd *tree, char **envp)
{
	char	*filename;
	pid_t	cpid;
	int		cp_status;

	filename = ft_strjoin_free(ft_strdup(".tempfiles/tempheredoc"),
                                ft_itoa(get_next_rn()));
	cpid = fork();
	if (cpid == -1)
		return (perror(FORK_ERROR), NULL);
	else if (cpid == 0)
	{
		eof_str = ft_strdup(eof_str);
		ft_free_tree(tree);
		create_heredoc_file(filename, eof_str, envp);
	}
	free(eof_str);
	//free(eof_str);
	wait(&cp_status);
	if (WIFEXITED(cp_status))
	{
		if (WEXITSTATUS(cp_status) == 0)
			return (filename);
		else
		{
			free(filename);
			return (NULL);
		}
	}
	else
		;//TODO: Handle signals sent during heredoc
	return (NULL);
}

void	find_heredocs(t_cmd *cmd, t_cmd *start, char **envp)
{
	t_pipe	*pipe_node;
	t_redir	*redir_node;

	if (cmd->type == PIPE)
	{
		pipe_node = (t_pipe *)cmd;
		find_heredocs(pipe_node->left, start, envp);
		find_heredocs(pipe_node->right, start, envp);
	}
	else if (cmd->type == REDIR)
	{
		redir_node = (t_redir *)cmd;
		if (redir_node->redir_type == '-')
			redir_node->file = heredoc(redir_node->file, start, envp);
		find_heredocs(redir_node->cmd, start, envp);
	}
}
