/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:04:34 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/20 18:26:10 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	place_var_in_envp(char *var, char ***envp)
{
	char	**new_envp;
	char	*new_var;
	int		envs_am;

	new_var = ft_strdup(var);
	if (!new_var)
		return (-1);
	envs_am = count_envs(*envp);
	new_envp = (char **)ft_calloc(envs_am + 2, sizeof(char *));
	if (!new_envp)
		return (free(new_var), -1);
	fill_new_envp(new_envp, envp);
	new_envp[envs_am] = new_var;
	free(*envp);
	*envp = new_envp;
	return (0);
}

void	handle_invalid_key(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	process_var(char **arg_ptr, char ***envp, char *key, char *value)
{
	if (ft_strnstr(*arg_ptr, "+=", ft_strlen(*arg_ptr)))
	{
		append_env_var(&(*arg_ptr), *envp);
		place_var_in_envp(*arg_ptr, envp);
	}
	else if (ft_strchr(*arg_ptr, '='))
	{
		delete_var(key, *envp);
		place_var_in_envp(*arg_ptr, envp);
	}
	else if (!value)
	{
		delete_var(key, *envp);
		place_var_in_envp(*arg_ptr, envp);
	}
}

int	place_vars_in_envp(char **argv, char ***envp)
{
	char	*key;
	int		i;
	char	*value;
	int		flag;

	i = 0;
	flag = 0;
	while (argv[++i])
	{
		key = get_key_from_var(argv[i]);
		value = get_env_value(key, *envp);
		if (!is_key_valid(key))
		{
			handle_invalid_key(argv[i]);
			flag = 1;
		}
		else
			process_var(&argv[i], envp, key, value);
		free(key);
		free(value);
	}
	return (flag);
}

int	ft_export(char **argv, char ***envp)
{
	char	*print_error;

	if (!argv[1])
		return (print_export_envs(*envp));
	if (argv[1][0] == '-' && argv[1][1] != '\0')
	{
		print_error = ft_strjoin_free(ft_strjoin("export: ", argv[1]),
				ft_strdup(": invalid option"));
		if (!print_error)
			return (errno);
		ft_print_error(print_error);
		free(print_error);
		return (INVALID_OPTION_CODE);
	}
	return (place_vars_in_envp(argv, envp));
}
