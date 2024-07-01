/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:20:29 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/01 11:00:57 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(t_localenv *env)
{
	char	path[PATH_MAX];

	if(getcwd(path, PATH_MAX))
	{
		ft_putendl_fd(path, 1);
		return ; // tem que se fazer secalhar a saida com os sinais
	}
	ft_putendl_fd(ft_getenv("PWD", env->content), 1);
	return ; // tem que se fazer secalhar a saida com os sinais
}

