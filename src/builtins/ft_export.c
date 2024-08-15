/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:21:16 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/14 23:17:22 by fivieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int print_export_envs(char **envp)
{
	char *key_equals;
	char *value;
	int i;

	i = -1;
	while (envp[++i])
	{
		key_equals = ft_strldup(envp[i], get_env_key_len(envp[i]) + 1);
		if (!key_equals)
			return (errno);
		value = ft_strdup(envp[i] + ft_strlen(key_equals));
		if (!value)
			return (free(key_equals), errno);
		ft_printf("declare -x %s", key_equals);
		if (key_equals[get_env_key_len(envp[i])] == '=')
			ft_printf("\"%s\"", value);
		write(1, "\n", 1);
		free(key_equals);
		free(value);
	}
	return (0);
}

/*int validate_argv(char **argv, char **envp)
{
	int i;
	int count;
	char *key;

	i = 0;
	count = 0;
	while (argv[++i])
	{
		if (is_key_valid(argv[i]))
		{
			key = get_env_key(argv[i]);
			if (!key)
				return (-1);
			delete_var(key, envp);
			count++;
			free(key);
		}
		else
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
		}
	}
	return (count);
}

int place_variables_in_envp(char **argv, char **new_envp, int count)
{
	int i;
	int error_code;

	i = 0;
	error_code = 0;
	while (argv[++i])
	{
		if (is_key_valid(argv[i]))
		{
			new_envp[count] = ft_strdup(argv[i]);
			if (!new_envp[count])
				return (-1);
			count += 1;
		}
		else
			error_code = 1;
	}
	return (error_code);
}*/
void set_env_var(char *key, char *value, char **envp)
{
    char *new_env_var;
    int i;

    // Cria a nova variável de ambiente
    new_env_var = ft_strjoin_free(ft_strjoin(key, "="), value);
    if (!new_env_var)
        return;

    i = 0;
    while (envp[i])
    {
        // Se já existe uma variável com o mesmo nome, substituímos
        if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0 && envp[i][ft_strlen(key)] == '=')
        {
            free(envp[i]);
            envp[i] = new_env_var;
            return;
        }
        i++;
    }

    // Se não existe, adicionamos ao final
    envp[i] = new_env_var;
    envp[i + 1] = NULL;  // Marca o fim da lista
}
int validate_argv(char **argv, char **envp)
{
    int i;
    int count;
    char *key;
    char *value;
    char *plus_equals;
    char *existing_value;

    i = 0;
    count = 0;
    while (argv[++i])
    {
        plus_equals = ft_strnstr(argv[i], "+=", ft_strlen(argv[i]));
        if (plus_equals)
        {
            key = ft_strldup(argv[i], plus_equals - argv[i]);
            if (!is_key_valid(key))
            {
                free(key);
                ft_putstr_fd("export: `", 2);
                ft_putstr_fd(argv[i], 2);
                ft_putstr_fd("': not a valid identifier\n", 2);
            }
            value = ft_strdup(plus_equals + 2);
            existing_value = get_env_value(key, envp);
            if (existing_value)
            {
                char *new_value = ft_strjoin_free(existing_value, value);
                set_env_var(key, new_value, envp);
				free(existing_value);
            }
            else
            {
                set_env_var(key, value, envp);
            }
            free(key);
            free(value);
            count++;
        }
        else if (is_key_valid(argv[i]))
        {
            key = get_env_key(argv[i]);
            if (!key)
                return (-1);
            delete_var(key, envp);
            count++;
            free(key);
        }
        else
        {
            ft_putstr_fd("export: `", 2);
            ft_putstr_fd(argv[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
        }
    }
    return (count);
}
int place_variables_in_envp(char **argv, char **new_envp, int count)
{
    int i;
    int error_code;
    char *key;
    char *value;
    char *current_value;
    char *plus_sign;
    char *equals_sign;

    i = 0;
    error_code = 0;
    while (argv[++i])
    {
        equals_sign = ft_strchr(argv[i], '=');
        plus_sign = ft_strnstr(argv[i], "+=", equals_sign - argv[i]);

        if (plus_sign && equals_sign)
        {
            key = ft_strldup(argv[i], plus_sign - argv[i]);
            value = ft_strdup(equals_sign + 1);
            current_value = get_env_value(key, new_envp); // Obtém o valor atual da variável

            if (current_value)
            {
                // Concatena o valor atual com o novo valor
                char *new_value = ft_strjoin(current_value, value);
                free(value); // Liberando o valor original
                value = new_value; // `value` agora aponta para a nova string
                free(current_value); // Liberar o valor antigo
            }
        }
        else if (equals_sign)
        {
            key = ft_strldup(argv[i], equals_sign - argv[i]);
            value = ft_strdup(equals_sign + 1);
        }
        else
        {
            key = ft_strdup(argv[i]);
            value = NULL;
        }

        if (is_key_valid(key))
        {
            char *temp_str = NULL;

            if (value)
            {
                temp_str = ft_strjoin(key, "=");
                temp_str = ft_strjoin_free(temp_str, value);
            }
            else
            {
                temp_str = ft_strdup(key);
            }

            if (!temp_str)
                return (-1);

            new_envp[count] = temp_str;
            count += 1;
        }
        else
        {
            error_code = 1;
        }

        free(key);
    }
    return (error_code);
}

int	ft_export(char **argv, char ***envp)
{
	char	**new_envp;
	int		count;
	int		error_code;
	char	*print_error;

	if (!argv[1])
		return (print_export_envs(*envp));
	if(argv[1][0] == '-' && argv[1][1] != '\0')
	{
		print_error = ft_strjoin_free(ft_strjoin("export: ", argv[1]), ft_strdup(": invalid option"));
		if (!print_error)
			return (errno);
		ft_print_error(print_error);
		free(print_error);
		return (2);
	}
	count = validate_argv(argv, *envp);
	if (count < 0)
		return (errno);
	new_envp = (char **)ft_calloc(count_envs(*envp) + count + 1,
			sizeof(char *));
	if (!new_envp)
		return (errno);
	count = fill_new_envp(new_envp, envp);
	error_code = place_variables_in_envp(argv, new_envp, count);
	if (error_code < 0)
		return (errno);
	free(*envp);
	*envp = new_envp;
	return (error_code);
}
