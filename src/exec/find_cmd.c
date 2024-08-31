/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:36:08 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/31 18:45:10 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include "exec_int.h"

static char	*find_path(char *cmd, char *envs, int *status);
static char	*cmd_is_accessable(char *path, char *cmd, int *status);
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
	if (cmd == NULL || ft_strlen(cmd) == 0
		|| ft_strcmp(cmd, "..") == 0 || ft_strcmp(cmd, ".") == 0)
	{
		*status = CMD_NOT_FOUND;
		return (NULL);
	}
	full = ft_strjoin_with_sep(path, cmd, '/');
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
