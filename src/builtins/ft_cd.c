/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:20:02 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/20 11:29:29 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	save_cwd(char *cwd, size_t size)
{
	if (getcwd(cwd, size) == NULL)
		return (errno);
	return (0);
}

int	verify_change_dir(char *dir)
{
	if (dir == NULL)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	else if (chdir(dir) != 0)
	{
		perror(dir);
		errno = 0;
		free(dir);
		return (1);
	}
	free(dir);
	return (0);
}

int	cd_dash(char ***envp)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", *envp);
	if (oldpwd == NULL)
	{
		ft_print_error("cd: OLDPWD not set");
		return (1);
	}
	printf("%s\n", oldpwd);
	if (verify_change_dir(oldpwd) != 0)
		return (errno);
	return (0);
}

int	ft_cd(char **argv, char ***envp)
{
	char	cwd[1024];
	char	*new_dir;

	if (argv[1] && is_option(argv[1]))
		return (handle_error_option(argv[1]));
	if (argv[1] && argv[2])
		return (ft_print_error("cd: too many arguments"), 1);
	if (save_cwd(cwd, sizeof(cwd)) != 0)
		return (-1);
	if (!argv[1])
		return (handle_home_directory(envp));
	else if (ft_strlen(argv[1]) == 1 && argv[1][0] == '-')
		return (cd_dash(envp));
	else if (argv[1][0] == '\0')
		return (0);
	else
	{
		new_dir = ft_strdup(argv[1]);
		if (!new_dir)
			return (errno);
		if (verify_change_dir(new_dir) != 0)
			return (1);
	}
	update_directories(cwd, envp);
	return (0);
}
