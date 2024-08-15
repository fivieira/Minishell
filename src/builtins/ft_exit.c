/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:22:49 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/13 11:49:19 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char **argv, char ***envp)
{
	(void)envp;
	(void)argv;
	ft_print_error("Something unexpected occured");
	return (0);
}

static int	get_exit_code_from_arg(char *arg)
{
	int	i;
	
	i = 0;
	if (!ft_isdigit(arg[i]) && arg[i] != '-' && arg[i] != '+')
		return (-1);
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
			return (-1);
	}
	return (ft_atoi(arg) % 255);
}

static int	parse_exit_arguments(t_root *r, char **args)
{
	int	exit_code;

	if (args[1])
	{
		exit_code = get_exit_code_from_arg(args[1]);
		
		if (exit_code == -1)
		{
			ft_matrix_free((void ***)&args);
			exit_with_standard_error(r, "exit: numeric arguments required", 2, 0);
		}
		if (args[2])
		{
			ft_matrix_free((void ***)&args);
			return(ft_print_error("exit: too many arguments"), 1);
		}
		ft_matrix_free((void ***)&args);
		free_everything_exit(r, exit_code);
	}
	ft_matrix_free((void ***)&args);
	free_everything_exit(r, r->prev_exit_code);
	return (0);
}

void	ft_exit_parent(t_root *r, t_exec *node)
{
	char	**args;

	ft_putstr_fd("exit\n", 2);
	args = create_args(node->argv);
	if (!args)
		exit_with_standard_error(r, "malloc", errno, 0);
	r->exit_code = parse_exit_arguments(r, args);
}

void	ft_exit_pipeline(t_root *r, t_exec *node)
{
	char	**args;

	args = create_args(node->argv);
	if (!args)
		exit_with_standard_error(r, "malloc", errno, 0);
	r->exit_code = parse_exit_arguments(r, args);
	free_everything_exit(r, r->exit_code);
}