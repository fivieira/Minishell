/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_root.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:20:10 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/19 22:38:07 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	create_shlvl(t_root *r)
{
	char	*old_shlvl;
	char	*new_shlvl;

	old_shlvl = get_env_value("SHLVL", r->envp);
	if (errno)
		return (-1);
	if (old_shlvl)
	{
		new_shlvl = ft_itoa(ft_atoi(old_shlvl) + 1);
		if (!new_shlvl)
			return (free(old_shlvl), -1);
		if (update_env("SHLVL", new_shlvl, &r->envp) != 0)
			return (free(old_shlvl), free(new_shlvl), -1);
		free(old_shlvl);
		free(new_shlvl);
	}
	else
	{
		if (place_var_in_envp("SHLVL=1", &r->envp) != 0)
			return (-1);
	}
	return (0);
}

static int	create_lastcmd(t_root *r)
{
	char	*lastcmd;

	lastcmd = get_env_value("_", r->envp);
	if (errno)
		return (-1);
	if (!lastcmd)
	{
		if (place_var_in_envp("_=]", &r->envp) != 0)
			return (-1);
	}
	else
		free(lastcmd);
	return (0);
}

static int	create_pwd(t_root *r)
{
	char	*pwd;

	pwd = get_env_value("PWD", r->envp);
	if (errno)
		return (-1);
	if (!pwd)
	{
		pwd = ft_strjoin_free(ft_strdup("PWD="), getcwd(NULL, 0));
		if (!pwd)
			return (-1);
		if (place_var_in_envp(pwd, &r->envp) != 0)
			return (free(pwd), -1);
		free(pwd);
	}
	else
		free(pwd);
	return (0);
}

static int	create_default_envs(t_root *r)
{
	if (create_shlvl(r) != 0)
		return (-1);
	if (create_lastcmd(r) != 0)
		return (-1);
	if (create_pwd(r) != 0)
		return (-1);
	return (0);
}

void	init_root(t_root *r, char **envp)
{
	r->line = NULL;
	r->envp = (char **)ft_matrix_dup((void **)envp);
	if (!r->envp)
		exit_in_init("malloc", r);
	if (create_default_envs(r) != 0)
		exit_in_init("getcwd", r);
	getcwd(r->tempfiles_dir, BUFFER_MAX_SIZE);
	if (errno)
		exit_in_init("getcdw", r);
	ft_strlcat(r->tempfiles_dir, TEMPFILES_DIR, BUFFER_MAX_SIZE);
	r->token_lst = NULL;
	r->tree = NULL;
	r->stoken = NULL;
	r->exit_code = 0;
	r->prev_exit_code = 0;
}
