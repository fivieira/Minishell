/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:09:41 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/14 21:58:33 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_envs(char **envp)
{
	int count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

int	fill_new_envp(char **new, char ***old_ref)
{
	char	**old;
	int		i;

	old = *old_ref;
	i = -1;
	while (old[++i])
		new[i] = old[i];
	return (i);
}
