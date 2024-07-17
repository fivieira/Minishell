/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:04:21 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/16 15:33:22 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_next_rn(void)
{
	static uint16_t	seed = 0;
	uint16_t	a;
	uint16_t	b;

	a = seed << 8;
	a = seed ^ a;
	seed = (a << 8) | ((a & 0xFF00) >> 8);
	a = seed ^ ((a & 0xFF) << 1);
	b = a >> 1;
	b = b ^ 0b1111111110000000;
	if (a % 2 == 0)
	{
		if (b == ((uint16_t)43605))
			seed = 0;
		else
			seed = b ^ 0b0001111111110100;
	}
	else
		seed = b ^ 0b1000000110000000;
	return ((int)seed);
}	

char	*create_heredoc_file(char *eof_str)
{
	char	*line;
	char	*filename;
	int	fd;

	filename = ft_strjoin_free(ft_strdup(".tempfiles/tempheredoc"), ft_itoa(get_next_rn()));
	fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	line = readline(">");
	while (ft_strncmp(line, eof_str, ft_strlen(eof_str) + 1) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(line);
	close(fd);
	return (filename);
}

t_cmd	*parse_redir(t_cmd *cmd, t_token **ptr)
{
	char	c;
	char	*heredoc_filename;

	c = (*ptr)->type;
	if (c == '<')
		cmd = redir_cmd(cmd, (*ptr)->content, O_RDONLY, 0);
	else if (c == '-')
	{
		heredoc_filename = create_heredoc_file((*ptr)->content);
		cmd = redir_cmd(cmd, heredoc_filename, O_RDONLY, 0);
	}
	else if (c == '>')
		cmd = redir_cmd(cmd, (*ptr)->content, O_WRONLY|O_CREAT|O_TRUNC, 1);
	else if (c == '+')
		cmd = redir_cmd(cmd, (*ptr)->content, O_WRONLY|O_CREAT|O_APPEND, 1);
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
			full_cmd = parse_redir(full_cmd, ptr);
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
	t_token *ptr;

	ptr = tokenlst;
	tree = parse_pipe(&ptr, envp);
	ft_free_tokenlst(tokenlst, false);
	return (tree);
}
