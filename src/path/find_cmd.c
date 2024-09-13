/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:36:08 by syamasaw          #+#    #+#             */
/*   Updated: 2024/09/13 06:15:52 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include "path_int.h"

static int	check_invaild_cmd(char *cmd, int *status);
static void	find_cmd_error_handling(int status_int, char *cmd);

char	*find_cmd(char *cmd, char **env, int *status)
{
	char	*full_path;
	int		status_int;

	full_path = NULL;
	*status = CMD_NOT_FOUND;
	status_int = COMMAND_NOT_FOUND;
	if (check_invaild_cmd(cmd, status))
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
	{
		full_path = cmd_is_accessable(NULL, cmd, status, &status_int);
		if (status_int == COMMAND_NOT_FOUND)
			status_int = NO_SUCH_FILE_OR_DIR;
	}
	while (ft_strchr(cmd, '/') == NULL && *env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			full_path = find_path(cmd, *env, status, &status_int);
			break ;
		}
		env ++;
	}
	find_cmd_error_handling(status_int, cmd);
	return (full_path);
}

static int	check_invaild_cmd(char *cmd, int *status)
{
	if (ft_strlen(cmd) == 0
		|| ft_strcmp(cmd, "..") == 0 || ft_strcmp(cmd, ".") == 0)
	{
		*status = CMD_NOT_FOUND;
		cmdnotfound_error(cmd);
		return (ERR);
	}
	return (OK);
}

static void	find_cmd_error_handling(int status_int, char *cmd)
{
	if (status_int == NO_SUCH_FILE_OR_DIR)
		no_such_file_or_directory_error(cmd);
	else if (status_int == IS_A_DIR)
		is_a_directory_error(cmd);
	else if (status_int == PERMISSION_DENIED)
		permission_denied_error(cmd);
	else if (status_int == COMMAND_NOT_FOUND)
		cmdnotfound_error(cmd);
	return ;
}
