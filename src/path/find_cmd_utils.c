/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:36:08 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/31 23:03:20 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_int.h"
#include <sys/stat.h>

char	*find_path(char *cmd, char *envs, int *status, int *status_int)
{
	char	**paths;
	char	*full;
	size_t	i;

	paths = ft_split(envs + 5, ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	full = NULL;
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

char	*cmd_is_accessable(
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

int	cmd_find_access_check(char *full_path, int *status, int *status_int)
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
		*status_int = COMMAND_NOT_FOUND;
	}
	else if (access(full_path, F_OK) == 0 && access(full_path, X_OK) != 0)
	{
		*status = CMD_CNT_EXECUTE;
		*status_int = PERMISSION_DENIED;
	}
	return (ERR);
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (ERR);
	return (S_ISDIR(path_stat.st_mode));
}

void	free_char_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i ++;
	}
	free(arr[i]);
	free(arr);
	return ;
}
