/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value_hd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:15:54 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/02 16:44:22 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/heredoc.h"

void	close_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static char	*search_and_return_value(char *key, int len)
{
	int		fd;
	char	*line;
	char	*value;

	fd = create_envp_file();
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(key, line, len) == 0 && (line)[len] == '=')
		{
			value = ft_strdup(line + len + 1);
			value[ft_strlen(value) - 1] = '\0';
			return (close_gnl(fd), free(line), free(key), value);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(key);
	return (NULL);
}

char	*get_env_value_hd(char *start)
{
	char	*key;
	int		len;

	key = get_env_key(start);
	if (!key)
		return (NULL);
	if (*key == '\0')
		return (free(key), ft_strdup("$"));
	len = ft_strlen(key);
	return (search_and_return_value(key, len));
}

int	create_envp_file(void)
{
	int		fd;
	char	*envp_filename;

	envp_filename = ft_strjoin(get_tempfiles_folder(), ENVP_FILENAME);
	if (!envp_filename)
		return (0);
	fd = open(envp_filename, O_RDONLY);
	free(envp_filename);
	if (fd < 0)
		return (0);
	return (fd);
}
