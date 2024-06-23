/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:24:57 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/23 13:42:33 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	Dprint_token(char *start, char *end)
{
	while (start < end)
	{
		write(1, start, 1);
		start++;
	}
	write(1, "\n", 1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*token;
	char	*etoken;

	if (argc != 1)
		return (printf(LAUNCH_ERROR), 0);
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline(PROMPT);
		while (line != line + ft_strlen(line))
		{
			printf("-------------NEW TOKEN FOUND-------------\n");
			printf("Token symbol: %c\n",
					get_token(&line, line + ft_strlen(line),
						&token, &etoken));
			Dprint_token(token, etoken);
			printf("Rest of string: %s\n", line);
		}
	}
	return (0);
}
