/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_int.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:46:14 by saraki            #+#    #+#             */
/*   Updated: 2024/08/31 21:35:51 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_INT_H
# define PATH_INT_H

# include "common.h"

char	*path_resolving(char *abspath);
char	*find_cmd(char *cmd, char **env, int *status);
int		is_directory(char *path);
void	free_char_arr(char **arr);

enum e_FIND_CMD_STATUS
{
	NO_SUCH_FILE_OR_DIR = 1,
	IS_A_DIR = 2,
	PERMISSION_DENIED = 3,
	COMMAND_NOT_FOUND = 4,
};

#endif