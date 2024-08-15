/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:52:41 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/31 09:32:19 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static int	expand_update(char **final, char **ptr)
{
	char	*env_value;

	if (**ptr == '$')
	{
		*ptr += 1;
		env_value = get_env_value_hd(*ptr);
		*final = ft_strjoin_free(*final, env_value);
		if (!*final)
			return (-1);
		*ptr += get_env_key_len(*ptr);
	}
	else
	{
		if (update_token(final, ft_strldup(*ptr, 1)) != 0)
		{
			free(*final);
			return (-1);
		}
		*ptr += 1;
	}
	return (0);
}

char	*find_and_expand(char *line)
{
	char	*final;
	char	*ptr;

	final = ft_strdup("");
	ptr = line;
	if (!final)
		return (NULL);
	while (*ptr)
	{
		if (expand_update(&final, &ptr) != 0)
			return (NULL);
	}
	free(line);
	return (final);
}
