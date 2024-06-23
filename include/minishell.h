/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:22:19 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/06/23 13:24:42 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //for printf
# include <readline/readline.h> // for rl library
# include <readline/history.h> // for rl history functionality
# include "../libft/libft.h"

# define PROMPT "WRITE SOMETHING, BITCH: "
# define LAUNCH_ERROR "Did you actually give arguments to launch a shell?\nWhat are you, some kind of idiot?\n"

// characher sets for token delimitation
# define WHITESPACE " \t\r\n\v"
# define TOKEN_DELIMS " <>|$"

char	get_token(char **ps, char *es, char **t, char **et);

#endif
