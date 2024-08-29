/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:22:04 by fivieira          #+#    #+#             */
/*   Updated: 2024/08/20 11:28:12 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_error_option(char *arg)
{
	char	*error_msg;

	error_msg = ft_strjoin_free(ft_strjoin("cd: ", arg),
			ft_strdup(": invalid option"));
	if (!error_msg)
		return (errno);
	ft_print_error(error_msg);
	free(error_msg);
	return (INVALID_OPTION_CODE);
}

int	handle_home_directory(char ***envp)
{
	char	*home_dir;

	home_dir = get_env_value("HOME", *envp);
	if (!home_dir)
		return (ft_print_error("cd: HOME not set"), 1);
	if (verify_change_dir(home_dir) != 0)
		return (1);
	return (0);
}

void	update_directories(char *cwd, char ***envp)
{
	update_env("OLDPWD", cwd, envp);
	if (save_cwd(cwd, 1024) != 0)
	{
		ft_print_error("Error saving current working directory");
		return ;
	}
	update_env("PWD", cwd, envp);
}
