/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tempfiles_folder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:46:36 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/02 10:53:53 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*setget_tempfiles_folder(int action, char *path_to_set)
{
	static char	*path;

	if (action == SET)
		path = path_to_set;
	else
		return (path);
	return (NULL);
}

void	init_tempfiles_path(char *path_to_set)
{
	setget_tempfiles_folder(SET, path_to_set);
}

char	*get_tempfiles_folder(void)
{
	return (setget_tempfiles_folder(GET, NULL));
}
