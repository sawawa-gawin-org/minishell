/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:36:08 by syamasaw          #+#    #+#             */
/*   Updated: 2024/07/01 06:48:13 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include "exec_int.h"

static char	*find_path(char *cmd, char *envs, int *status);
static char	*cmd_is_accessable(char *path, char *cmd, int *status);
static char	*join_path_cmd(char *path, char *cmd);
static void	free_char_arr(char **arr);

char	*find_cmd(char *cmd, char **env, int *status)
{
	int		i;
	char	*full;

	i = 0;
	full = cmd_is_accessable(NULL, cmd, status);
	if (full != NULL)
		return (full);
	if (*status == CMD_CNT_EXECUTE)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (find_path(cmd, env[i], status));
		i ++;
	}
	return (NULL);
}

static char	*find_path(char *cmd, char *envs, int *status)
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
		full = cmd_is_accessable(paths[i], cmd, status);
		if (full != NULL)
			break ;
		i++;
	}
	free_char_arr(paths);
	return (full);
}

static char	*cmd_is_accessable(char *path, char *cmd, int *status)
{
	char	*full;

	*status = 1;
	full = join_path_cmd(path, cmd);
	if (full == NULL)
		return (NULL);
	if (access(full, X_OK) == 0)
	{
		*status = 0;
		return (full);
	}
	if (access(full, F_OK) != 0 && access(full, X_OK) != 0)
		*status = CMD_NOT_FOUND;
	else if (access(full, F_OK) == 0 && access(full, X_OK) != 0)
		*status = CMD_CNT_EXECUTE;
	free(full);
	return (NULL);
}

static char	*join_path_cmd(char *path, char *cmd)
{
	char	*full;
	size_t	path_len;
	size_t	cmd_len;

	if (cmd == NULL)
		return (NULL);
	if (path == NULL)
		return (ft_strdup(cmd));
	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	full = (char *) ft_calloc((path_len + cmd_len + 2), sizeof(char));
	if (full == NULL)
		return (NULL);
	ft_memcpy(full, path, path_len);
	ft_memcpy(full + path_len, "/", 1);
	ft_memcpy(full + path_len + 1, cmd, cmd_len);
	return (full);
}

static void	free_char_arr(char **arr)
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
