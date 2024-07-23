/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:20:29 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/23 18:23:25 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(char **argv, char **envp)
{
	char	path[PATH_MAX];

	(void)argv;
	(void)envp;
	if (getcwd(path, PATH_MAX)) //TODO: easier and safer to receive the path as the return value?
	{
		ft_putendl_fd(path, 1);
		return (0);
	}
	return (errno);
}

/*
int	pwd(t_localenv *env)
{
	char	path[PATH_MAX];
	char	*out;

	if (getcwd(path, PATH_MAX))
	{
		ft_putendl_fd(path, 1);
		return (exit_code(EXIT_SUCCESS));
	}
	if (ft_getenv("PWD", &out, env->content) != 0)
		return (ft_getenv("PWD", &out, env->content));// getenv returns 
	ft_putendl_fd(out, 1);
	return (exit_code(EXIT_SUCCESS));
}*/
