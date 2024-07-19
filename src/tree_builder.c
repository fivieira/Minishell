/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:04:21 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/18 21:37:14 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_and_expand(char **line, char **envp)
{
	char	*final;
	char	*ptr;
	int	status;
	
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
	free(line);
	*line = final;
	return (0);
}

char	*create_heredoc_file(char *eof_str, char **envp)
{
	char	*line;
	char	*filename;
	int		fd;

	//TODO: Create fork, and free all memory in child, so SIGINT doesnt leak.
	filename = ft_strjoin_free(ft_strdup(".tempfiles/tempheredoc"),
			ft_itoa(get_next_rn()));
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	line = readline(">");
	while (line && ft_strncmp(line, eof_str, ft_strlen(eof_str) + 1) != 0)
	{
		if (find_and_expand(&line, envp) != 0)
			return (NULL);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(eof_str);
	free(line);
	close(fd);
	//handle_sigint_status();
	return (filename);
}

t_cmd	*parse_redir(t_cmd *cmd, t_token **ptr, char **envp)
{
	char	c;
	char	*heredoc_filename;

	c = (*ptr)->type;
	if (c == '<')
		cmd = redir_cmd(cmd, (*ptr)->content, O_RDONLY, 0);
	else if (c == '-')
	{
		heredoc_filename = create_heredoc_file((*ptr)->content, envp);
		cmd = redir_cmd(cmd, heredoc_filename, O_RDONLY, 0);
	}
	else if (c == '>')
		cmd = redir_cmd(cmd, (*ptr)->content, O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (c == '+')
		cmd = redir_cmd(cmd, (*ptr)->content, O_WRONLY | O_CREAT | O_APPEND, 1);
	return (cmd);
}

t_cmd	*parse_exec(t_token **ptr, char **envp)
{
	t_cmd	*full_cmd;
	t_exec	*exec_node;

	full_cmd = exec_cmd(envp);
	exec_node = (t_exec *)full_cmd;
	while (*ptr && (*ptr)->type != '|')
	{
		if ((*ptr)->type == 'a')
			ft_lstadd_back(&(exec_node->argv), ft_lstnew((*ptr)->content));
		else
			full_cmd = parse_redir(full_cmd, ptr, envp);
		*ptr = (*ptr)->next;
	}
	return (full_cmd);
}

t_cmd	*parse_pipe(t_token **ptr, char **envp)
{
	t_cmd	*node;

	node = parse_exec(ptr, envp);
	if (*ptr && (*ptr)->type == '|')
	{
		*ptr = (*ptr)->next;
		node = pipe_cmd(node, parse_pipe(ptr, envp));
	}
	return (node);
}

t_cmd	*tree_builder(t_token *tokenlst, char **envp)
{
	t_cmd	*tree;
	t_token	*ptr;

	ptr = tokenlst;
	tree = parse_pipe(&ptr, envp);
	ft_free_tokenlst(tokenlst, false);
	return (tree);
}
