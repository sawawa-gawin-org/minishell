/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 05:46:45 by syamasaw          #+#    #+#             */
/*   Updated: 2024-08-21 05:46:45 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	is_a_directory_error(char *filepath)
{
	char	*prefix;
	char	*msg;

	prefix = MSG_PREFIX;
	msg = ": Is a directory\n";
	if (write(STDERR_FILENO, prefix, ft_strlen(prefix)) == -1)
		perror("write");
	if (write(STDERR_FILENO, filepath, ft_strlen(filepath)) == -1)
		perror("write");
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) == -1)
		perror("write");
	return (ERR);
}

int	permission_denied_error(char *filepath)
{
	char	*prefix;
	char	*msg;

	prefix = MSG_PREFIX;
	msg = ": Permission denied\n";
	if (write(STDERR_FILENO, prefix, ft_strlen(prefix)) == -1)
		perror("write");
	if (write(STDERR_FILENO, filepath, ft_strlen(filepath)) == -1)
		perror("write");
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) == -1)
		perror("write");
	return (ERR);
}

int	no_such_file_or_directory_error(char *filepath)
{
	char	*prefix;
	char	*msg;

	prefix = MSG_PREFIX;
	msg = ": No such file or directory\n";
	if (write(STDERR_FILENO, prefix, ft_strlen(prefix)) == -1)
		perror("write");
	if (write(STDERR_FILENO, filepath, ft_strlen(filepath)) == -1)
		perror("write");
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) == -1)
		perror("write");
	return (ERR);
}
