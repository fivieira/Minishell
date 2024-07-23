/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:20:29 by fivieira          #+#    #+#             */
<<<<<<< HEAD:src/builtins/ft_pwd.c
/*   Updated: 2024/07/23 12:33:02 by ndo-vale         ###   ########.fr       */
=======
/*   Updated: 2024/07/22 23:35:40 by fivieira         ###   ########.fr       */
>>>>>>> 67b05ab44944c12d7f42767f2fab46e24caf3baf:src/builtins/pwd.c
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

<<<<<<< HEAD:src/builtins/ft_pwd.c

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
