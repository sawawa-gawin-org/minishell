/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:13:18 by saraki            #+#    #+#             */
/*   Updated: 2024/08/31 18:45:10 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"
#include "dbllst.h"
#include "libft.h"

static int	normalize_path(
				char *path, t_blst *envlst, t_cd_path_routing *routing);
static int	valid_option(
				char **cmd, char **path, int *options, t_blst *envlst);
static int	flag_parser(char *flag_str);

/**
 * @brief Executes the built-in command "cd".
 *
 * This function is responsible for changing the current working directory.
 *
 * @param cmd The command and its arguments.
 * @param envlst The list of environment variables.
 * @param mode The mode of execution.
 * @return Returns 0 on success, -1 on failure.
 */
int	builtin_cd(char **cmd, t_blst **envlst, int mode)
{
	t_cd_path_routing	routing;
	int					status;
	char				*path;
	int					options;
	int					err;

	if (mode == IS_CHILD_PROCESS)
		return (OK);
	status = valid_option(cmd, &path, &options, *envlst);
	if (status > 0)
		return (status);
	if (normalize_path(path, *envlst, &routing) > 0)
		return (ERR_ALLOCATE_MEMORY);
	err = cd_check_err(path, &routing);
	if (err == ERR_ALLOCATE_MEMORY || err == GENERAL_ERR)
		return (err);
	status = update_pwd_and_oldpwd_env(routing.src, routing.dist, envlst);
	free_all_params(&routing);
	if (status != OK)
		return (status);
	return (OK);
}

/**
 * @brief Normalize the given path.
 *
 * This function takes a path as input and normalizes it by removing any
 * redundant slashes and resolving any relative path components.
 * The normalized path is then returned.
 *
 * @param path The path to be normalized.
 * @return The normalized path.
 */
static int	normalize_path(
				char *path, t_blst *envlst, t_cd_path_routing *routing)
{
	char	*abspath;

	routing->src = allocate_cwd_path(envlst);
	if (routing->src == NULL)
		return (ERR);
	if (path[0] != '/')
		abspath = ft_strjoin_with_sep(routing->src, path, '/');
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

static int	valid_option(char **cmd, char **path, int *options, t_blst *envlst)
{
	size_t	i;
	int		flag_value;

	*path = NULL;
	i = 1;
	while (cmd[i] != NULL && ft_strncmp(cmd[i], "-", 1) == 0)
	{
		flag_value = flag_parser(cmd[i]);
		if (flag_value == ERR)
			return (cd_option_err(cmd[i]));
		*options |= flag_value;
		i++;
	}
	if (cmd[i] != NULL)
		*path = cmd[i];
	else if (cmd[i] != NULL && cmd[i + 1] != NULL)
		return (cd_argc_err());
	else
		return (get_home_path(path, envlst));
	return (OK);
}

static int	flag_parser(char *flag_str)
{
	int		flag;

	flag_str ++;
	flag = 0;
	while (*flag_str)
	{
		if (*flag_str == 'L')
			flag |= L_FLAG;
		else if (*flag_str == 'P')
			flag |= P_FLAG;
		else if (*flag_str == 'e')
			flag |= E_FLAG;
		else if (*flag_str == '@')
			flag |= AT_FLAG;
		else
			return (ERR);
		flag_str++;
	}
	return (flag);
}

void	free_all_params(t_cd_path_routing *param)
{
	if (param->src != NULL)
		free(param->src);
	if (param->dist != NULL)
		free(param->dist);
	return ;
}
