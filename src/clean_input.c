/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:47:53 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/01 21:18:50 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_single_quoted(char **cmd, char **out)
{
	char	*tmp;
	int	count;

	count = 0;
	while ((*cmd)[count] != '\'')
	{
		if ((*cmd)[count] == '\0')
			return -1; //TODO: SYNTAX ERROR: NO CLOSING SINGLE QUOTE
		count++;
	}
	tmp = (char *)ft_calloc(count + 1, sizeof(char));
	ft_strlcpy(tmp, *cmd, count + 1);
	*out = ft_strjoin(*out, tmp);
	free(tmp);
	*cmd += count + 1;
	return (count);
}

char	*str_cappend(char* str, char c)
{
	char	*out;
	int	len;

	len = ft_strlen(str);
	out = (char *)ft_calloc(len + 2, sizeof(char));
	ft_strlcpy(out, str, len + 1);
	out[len] = c;
	return (out);
}

char    *clean_input(char *cmd)
{
        char    *out;
        int     flags;
        int     count;

        out = ft_strdup("");
        flags = 1 << F_PIPE;
	count = 0;
	printf("%s\n", cmd);
        if (!out)
                return (NULL); //TODO: DEAL WITH ERROR
        while (*cmd)
        {
		printf("%c\n", *cmd);
		if (is_fon(flags, F_OPEN_SINGLE))
		{
			count += get_single_quoted(&cmd, &out);
			printf("%c\n", *cmd);
			set_flag(&flags, F_OPEN_SINGLE, false);
		}
		else if (*cmd == '\'')
		{
			set_flag(&flags, F_OPEN_SINGLE, true);
			cmd += 1;
		}
		else
		{
			out = str_cappend(out, *cmd); 
			cmd += 1;
			count++;
		}
        }
	printf("%i: %s", count, out); //TODO: FIX LEAKS
	return (out);
}

int	main(int argc, char **argv)
{
	(void)argc;
	clean_input(argv[1]);
}
