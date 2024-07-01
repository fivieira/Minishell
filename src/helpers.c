/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:26:58 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/01 12:21:06 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_fon(int flags, int f)
{
	return (flags & 1 << f);
}

void	set_flag(int *flags, int f, bool set)
{
	if (set)
		*flags = *flags | 1 << f;
	else
		*flags = *flags & ~(1 << f);
}
