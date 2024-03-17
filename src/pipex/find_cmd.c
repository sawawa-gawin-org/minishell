/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:36:08 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/17 14:26:11 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static char	*find_path(char *path, char *envs);
static int	path_length_checker(char *env_path, int i);

char	*find_cmd(char *path, char *envp[])
{
	int		i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (find_path(path, envp[i]));
	return (NULL);
}

static char	*find_path(char *path, char *envs)
{
	int		env;
	int		path_len;
	int		index;
	char	*full;

	index = 5;
	path_len = ft_strlen(path);
	while (envs[index] == '/')
	{
		env = path_length_checker(envs, index);
		full = (char *)malloc((path_len + env + 2) * sizeof(char));
		if (!full)
			return (NULL);
		ft_memcpy(full, envs + index, env);
		ft_memcpy(full + env, "/", 1);
		ft_memcpy(full + env + 1, path, path_len);
		full[path_len + env + 1] = '\0';
		if (access(full, X_OK) == 0)
			return (full);
		index += env + 1;
		free(full);
	}
	return (NULL);
}

static int	path_length_checker(char *env_path, int i)
{
	int	len;

	len = 0;
	while (1)
	{
		if (env_path[len + i] == ':' || env_path[len + i] == '\0')
			break ;
		len++;
	}
	return (len);
}
