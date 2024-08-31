/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_int.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:46:14 by saraki            #+#    #+#             */
/*   Updated: 2024/08/31 23:05:37 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_INT_H
# define PATH_INT_H

# include "common.h"

char	*path_resolving(char *abspath);
char	*find_cmd(char *cmd, char **env, int *status);

char	*find_path(char *cmd, char *envs, int *status, int *status_int);
char	*cmd_is_accessable(
			char *path, char *cmd, int *status, int *status_int);
int		cmd_find_access_check(char *full_path, int *status, int *status_int);
int		is_directory(char *path);
void	free_char_arr(char **arr);

enum e_FIND_CMD_STATUS
{
	COMMAND_NOT_FOUND = 1,
	IS_A_DIR = 2,
	PERMISSION_DENIED = 3,
	NO_SUCH_FILE_OR_DIR = 4,
};

#endif