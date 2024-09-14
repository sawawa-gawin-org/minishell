/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:13:18 by saraki            #+#    #+#             */
/*   Updated: 2024/09/14 15:48:12 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"
#include "dbllst.h"
#include "libft.h"
#include "path.h"

static int	normalize_path(
				char *path, t_blst *envlst, t_cd_path_routing *routing);
static int	valid_option(char **cmd, char **path, t_blst *envlst);
static int	flag_parser(char *flag_str);
static int	update_pwd_and_oldpwd_env(
				char *old_pwd,
				char *new_pwd,
				t_blst **envlst);

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
	int					err;

	(void) mode;
	status = valid_option(cmd, &path, *envlst);
	if (status > 0)
		return (status);
	if (normalize_path(path, *envlst, &routing) > 0)
		return (ERR_ALLOCATE_MEMORY);
	err = cd_check_err(path, &routing);
	if (err == ERR_ALLOCATE_MEMORY || err == GENERAL_ERR)
		return (err);
	status = update_pwd_and_oldpwd_env(routing.src, routing.dist, envlst);
	if (routing.src != NULL)
		free(routing.src);
	if (routing.dist != NULL)
		free(routing.dist);
	return (status);
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

static int	valid_option(char **cmd, char **path, t_blst *envlst)
{
	int		flag_value;
	int		options;

	options = 0;
	cmd++;
	while (*cmd != NULL && !ft_strncmp(*cmd, "-", 1) && ft_strcmp(*cmd, "--"))
	{
		flag_value = flag_parser(*cmd);
		if (flag_value == ERR)
			return (MISUSE_OF_SHELL_BUILTINS);
		options |= flag_value;
		if (options & GO_OLDPWD && *(cmd + 1) == NULL)
			return (get_oldpwd_path(path, envlst));
		else if (options & GO_OLDPWD && *(cmd + 1) != NULL)
			return (cd_argc_err());
		cmd ++;
	}
	if (ft_strcmp(*cmd, "--") == 0)
		cmd ++;
	*path = *cmd;
	if (*cmd == NULL)
		return (get_home_path(path, envlst));
	else if (*cmd != NULL && *(cmd + 1) != NULL)
		return (cd_argc_err());
	return (OK);
}

static int	flag_parser(char *flag_str)
{
	size_t	i;
	int		flag;

	i = 1;
	flag = 0;
	if (ft_strcmp(flag_str, "-") == 0)
		return (GO_OLDPWD);
	while (flag_str[i])
	{
		if (flag_str[i] == 'L' || flag_str[i] == 'P'
			|| flag_str[i] == 'e' || flag_str[i] == '@')
		{
			cd_unimplemented_option_err(flag_str);
			return (ERR);
		}
		else
		{
			cd_option_err(flag_str);
			return (ERR);
		}
		i ++;
	}
	return (flag);
}

/**
 * Updates the PWD and OLDPWD environment variables with the given paths.
 *
 * @param old_pwd The old working directory path.
 * @param new_pwd The new working directory path.
 * @param envlst  A pointer to the linked list of environment variables.
 * @return        Returns OK on success, ERR on failure.
 * @note          It doesn't matter if the both parameters are allocated or not.
 */
static int	update_pwd_and_oldpwd_env(
				char *old_pwd,
				char *new_pwd,
				t_blst **envlst)
{
	int		status;

	if (old_pwd == NULL || new_pwd == NULL)
		return (GENERAL_ERR);
	status = OK;
	status = update_or_create_env("OLDPWD", old_pwd, envlst);
	if (status == OK)
		status = update_or_create_env("PWD", new_pwd, envlst);
	return (status);
}
