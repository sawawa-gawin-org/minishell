/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 03:31:04 by saraki            #+#    #+#             */
/*   Updated: 2024/06/22 08:04:42 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

int	cmdnotfound_error(char *cmd)
{
	char	*prefix;
	char	*suffix;

	prefix = "minishell: ";
	suffix = ": command not found\n";
	if (write(STDERR_FILENO, prefix, ft_strlen(prefix)) == -1)
		perror("write");
	if (write(STDERR_FILENO, cmd, ft_strlen(cmd)) == -1)
		perror("write");
	if (write(STDERR_FILENO, suffix, ft_strlen(suffix)) == -1)
		perror("write");
	return (ERR);
}
