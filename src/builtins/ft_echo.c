/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:29:53 by fivieira          #+#    #+#             */
/*   Updated: 2024/07/23 18:20:47 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	find_n(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (false);
	if (str[i] && str[i] == '-')
	{
		while (str[++i])
		{
			if (str[i] != 'n')
				return (false);
		}
		if (str[i - 1] == 'n')
			return (true);
	}
	return (false);
}

int	ft_echo(char **msg, char **envp)
{
	int		i;
	bool	flag;
	char	*temp;

	(void)envp;
	i = 0;
	flag = false;
	while (msg[++i] && find_n(msg[i]))
		flag = true;
	while (msg[i] != NULL)
	{
		temp = ft_strdup(msg[i]);
		if (!temp)
			return (errno);
		printf("%s", temp);
		free(temp);
		if (msg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (exit_code(EXIT_SUCCESS));
}
