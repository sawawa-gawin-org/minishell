/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 03:31:04 by saraki            #+#    #+#             */
/*   Updated: 2024/07/01 06:41:13 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	cmdnotfound_error(char *cmd)
{
	char	*prefix;
	char	*suffix;

	prefix = MSG_PREFIX;
	suffix = ": command not found\n";
	if (write(STDERR_FILENO, prefix, ft_strlen(prefix)) == -1)
		perror("write");
	if (write(STDERR_FILENO, cmd, ft_strlen(cmd)) == -1)
		perror("write");
	if (write(STDERR_FILENO, suffix, ft_strlen(suffix)) == -1)
		perror("write");
	return (ERR);
}

int	cmdnotexecutable_error(char *cmd)
{
	char	*prefix;
	char	*suffix;

	prefix = MSG_PREFIX;
	suffix = ": Permission denied\n";
	if (write(STDERR_FILENO, prefix, ft_strlen(prefix)) == -1)
		perror("write");
	if (write(STDERR_FILENO, cmd, ft_strlen(cmd)) == -1)
		perror("write");
	if (write(STDERR_FILENO, suffix, ft_strlen(suffix)) == -1)
		perror("write");
	return (ERR);
}
