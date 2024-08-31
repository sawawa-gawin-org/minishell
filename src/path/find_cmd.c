/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:36:08 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/31 21:38:27 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include "path_int.h"

static void	find_cmd_error_handling(int status_int, char *cmd);
static char	*find_path(char *cmd, char *envs, int *status, int *status_int);
static char	*cmd_is_accessable(
				char *path, char *cmd, int *status, int *status_int);
static int	cmd_find_access_check(
				char *full_path, int *status, int *status_int);

char	*find_cmd(char *cmd, char **env, int *status)
{
	int		i;
	char	*full_path;
	int		status_int;

	i = 0;
	*status = GENERAL_ERR;
	status_int = GENERAL_ERR;
	if (ft_strlen(cmd) == 0
		|| ft_strcmp(cmd, "..") == 0 || ft_strcmp(cmd, ".") == 0)
	{
		*status = CMD_NOT_FOUND;
		cmdnotfound_error(cmd);
		return (NULL);
	}
	if (ft_strchr(cmd, '/') != NULL)
		full_path = cmd_is_accessable(NULL, cmd, status, &status_int);
	while (ft_strchr(cmd, '/') == NULL && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			full_path = find_path(cmd, env[i], status, &status_int);
		i ++;
	}
	find_cmd_error_handling(status_int, cmd);
	return (full_path);
}

static void	find_cmd_error_handling(int status_int, char *cmd)
{
	if (status_int == NO_SUCH_FILE_OR_DIR)
		no_such_file_or_directory_error(cmd);
	else if (status_int == IS_A_DIR)
		is_a_directory_error(cmd);
	else if (status_int == PERMISSION_DENIED)
		permission_denied_error(cmd);
	return ;
}

static char	*find_path(char *cmd, char *envs, int *status, int *status_int)
{
	char	**paths;
	char	*full;
	size_t	i;

	paths = ft_split(envs + 5, ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		full = cmd_is_accessable(paths[i], cmd, status, status_int);
		if (full != NULL)
			break ;
		i++;
	}
	free_char_arr(paths);
	return (full);
}

static char	*cmd_is_accessable(
				char *path, char *cmd, int *status, int *status_int)
{
	char	*full_path;

	if (path == NULL)
		full_path = ft_strdup(cmd);
	else
		full_path = ft_strjoin_with_sep(path, cmd, '/');
	if (full_path == NULL)
	{
		malloc_error();
		return (NULL);
	}
	else if (cmd_find_access_check(full_path, status, status_int) == OK)
		return (full_path);
	free(full_path);
	return (NULL);
}

static int	cmd_find_access_check(char *full_path, int *status, int *status_int)
{
	if (is_directory(full_path) == 1)
	{
		*status = CMD_CNT_EXECUTE;
		*status_int = IS_A_DIR;
	}
	else if (access(full_path, X_OK) == 0)
	{
		*status = OK;
		*status_int = OK;
		return (OK);
	}
	else if (access(full_path, F_OK) != 0)
	{
		*status = CMD_NOT_FOUND;
		*status_int = NO_SUCH_FILE_OR_DIR;
	}
	else if (access(full_path, F_OK) == 0 && access(full_path, X_OK) != 0)
	{
		*status = CMD_CNT_EXECUTE;
		*status_int = PERMISSION_DENIED;
	}
	return (ERR);
}
