/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:16:46 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/23 00:00:23 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	find_and_expand(char **line, t_root *r)
{
	char	*final;
	char	*ptr;
	int		status;

	ptr = *line;
	final = ft_strdup("");
	if (!final)
		return (errno);
	while (*ptr)
	{
		if (*ptr == '$')
			status = ft_expand_env(&ptr, &final, r);
		else
		{
			status = update_token(&final, ptr, 1);
			ptr += 1;
		}
		if (status != 0)
			return (free(final), free(*line), errno);
	}
	free(*line);
	*line = final;
	return (0);
}

char	*create_heredoc_file(char *filename, char *eof_str, t_root *r)
{
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(filename);
	line = readline(">");
	while (line && ft_strncmp(line, eof_str, ft_strlen(eof_str) + 1) != 0)
	{
		if (find_and_expand(&line, r) != 0)
			exit (errno);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	if (!line)
		ft_putstr_fd(CTRLD_HEREDOC_MSG, 2);
	free(eof_str);
	free(line);
	close(fd);
	exit(EXIT_SUCCESS);
}

char	*heredoc(char *eof_str, t_root *r, int *status)
{
	char	*filename;
	pid_t	cpid;
	int		cp_status;

	filename = ft_strjoin_free(ft_strdup(".tempfiles/tempheredoc"),
                                ft_itoa(get_next_rn()));
	if (!filename)
	{
		*status = errno;
		return (NULL);
	}
	cpid = fork();
	if (cpid == -1)
		return (NULL);
	else if (cpid == 0)
	{
		eof_str = ft_strdup(eof_str);
		ft_free_tree(r->tree);
		create_heredoc_file(filename, eof_str, r);
	}
	free(eof_str);
	wait(&cp_status);
	if (WIFEXITED(cp_status))
	{
		if (WEXITSTATUS(cp_status) == 0)
			return (filename);
		else
		{
			free(filename);
			*status = WEXITSTATUS(cp_status);
			return (NULL);
		}
	}
	else
		handle_sigint_status();//TODO: Handle signals sent during heredoc
	return (NULL);
}

int	set_heredocs(t_cmd *cmd, t_root *r, int *status)
{
	t_pipe	*pipe_node;
	t_redir	*redir_node;

	if (cmd->type == PIPE)
	{
		pipe_node = (t_pipe *)cmd;
		if (set_heredocs(pipe_node->left, r, status)
			|| set_heredocs(pipe_node->right, r, status))
			return (*status);
	}
	else if (cmd->type == REDIR)
	{
		redir_node = (t_redir *)cmd;
		if (redir_node->redir_type == '-')
		{
			redir_node->file = heredoc(redir_node->file, r, status);
			if (!redir_node->file)
				return (*status);
		}
		if (set_heredocs(redir_node->cmd, r, status))
			return (*status);
	}
	return (*status);
}
