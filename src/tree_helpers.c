/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:54:24 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/18 11:54:42 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_next_rn(void)
{
	static uint16_t	seed = 0;
	uint16_t		a;
	uint16_t		b;

	a = seed << 8;
	a = seed ^ a;
	seed = (a << 8) | ((a & 0xFF00) >> 8);
	a = seed ^ ((a & 0xFF) << 1);
	b = a >> 1;
	b = b ^ 0b1111111110000000;
	if (a % 2 == 0)
	{
		if (b == ((uint16_t)43605))
			seed = 0;
		else
			seed = b ^ 0b0001111111110100;
	}
	else
		seed = b ^ 0b1000000110000000;
	return ((int)seed);
}
