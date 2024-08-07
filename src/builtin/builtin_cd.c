/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:13:18 by saraki            #+#    #+#             */
/*   Updated: 2024/08/07 01:17:36 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"
#include "dbllst.h"
#include "libft.h"

static int	normalize_path(
				char *path, t_blst *envlst, t_cd_path_routing *routing);
static int	valid_option(char **cmd, char **path);
static void	free_all_params(t_cd_path_routing *param);

int	builtin_cd(char **cmd, t_blst **envlst, int mode)
{
	t_cd_path_routing	routing;
	int					status;
	char				*path;

	if (mode == IS_CHILD_PROCESS)
		return (OK);
	status = valid_option(cmd, &path);
	if (status > 0)
		return (status);
	if (normalize_path(path, *envlst, &routing) > 0)
		return (ERR_ALLOCATE_MEMORY);
	if (chdir(routing.dist) == -1)
	{
		free_all_params(&routing);
		return (GENERAL_ERR);
	}
	status = update_pwd_and_oldpwd_env(routing.src, routing.dist, envlst);
	free_all_params(&routing);
	if (status != OK)
		return (status);
	return (OK);
}

static int	normalize_path(
				char *path, t_blst *envlst, t_cd_path_routing *routing)
{
	char	*normalized_path;
	char	*abspath;

	routing->src = allocate_cwd_path(envlst);
	if (routing->src == NULL)
		return (ERR);
	if (path[0] != '/')
		abspath = create_abspath(routing->src, path);
	else
		abspath = ft_strdup(path);
	if (abspath == NULL)
	{
		free(routing->src);
		return (ERR);
	}
	routing->dist = path_resolving(abspath);
	free(abspath);
	if (routing->dist == NULL)
	{
		free(routing->src);
		return (ERR);
	}
	return (OK);
}

static int	valid_option(char **cmd, char **path)
{
	if (cmd[1] != NULL)
	{
		env_argc_err();
		return (MISUSE_OF_SHELL_BUILTINS);
	}
	if (cmd[1][0] == '-')
	{
		if (ft_strcmp(cmd[1], "-L") == 0)
			return (OK);
	}
	*path = cmd[1]; // tmp
	return (OK);
}

static void	free_all_params(t_cd_path_routing *param)
{
	if (param->src != NULL)
		free(param->src);
	if (param->dist != NULL)
		free(param->dist);
	return ;
}
