/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:32:32 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/18 17:55:17 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*build_cmd_path(char *path, char *cmd)
{
	char	*path_slash;
	char	*final_path;

	path_slash = ft_strjoin(path, "/");
	final_path = ft_strjoin(path_slash, cmd);
	free(path_slash);
	return (final_path);
}

char	**get_cmd_folders(char **env)
{
	char	*path_str;
	char	**cmd_paths;
	int		i;

	i = -1;
	path_str = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_str = ft_strdup(env[i] + 5);
			break ;
		}
	}
	cmd_paths = ft_split(path_str, ':');
	free(path_str);
	if (!cmd_paths)
		return (NULL);
	return (cmd_paths);
}

char	*validate_cmd(char *cmd, char **env)
{
	char	*path_str;
	char	**cmd_paths;
	int		i;

	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	path_str = NULL;
	i = -1;
	cmd_paths = get_cmd_folders(env);
	while (cmd_paths && cmd_paths[++i])
	{
		free(path_str);
		path_str = build_cmd_path(cmd_paths[i], cmd);
		if (!path_str)
			return (ft_free_matrix((void **)cmd_paths), NULL);
		if (access(path_str, F_OK) == 0)
			return (ft_free_matrix((void **)cmd_paths), path_str);
	}
	free(path_str);
	ft_free_matrix((void **)cmd_paths);
	return (ft_strdup("INVALID"));
}
