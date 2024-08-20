/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects_out.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-20 08:04:59 by syamasaw          #+#    #+#             */
/*   Updated: 2024-08-20 08:04:59 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

int	open_existing_file_for_write(char *dist, int appendflag)
{
	struct stat	buf;
	int			fd;

	fd = -1;
	if (stat(dist, &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd(MSG_PREFIX, 2);
		ft_putstr_fd(dist, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		fd = -1;
	}
	else if (access(dist, W_OK) == -1)
	{
		ft_putstr_fd(MSG_PREFIX, 2);
		ft_putstr_fd(dist, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		fd = -1;
	}
	else if (appendflag == 0)
		fd = open(dist, O_WRONLY | O_TRUNC);
	else
		fd = open(dist, O_WRONLY | O_APPEND);
	return (fd);
}

int	open_file_for_read(char *dist)
{
	int	fd;

	fd = -1;
	if (access(dist, F_OK) == -1)
	{
		ft_putstr_fd(MSG_PREFIX, 2);
		ft_putstr_fd(dist, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		fd = -1;
	}
	else if (access(dist, R_OK) == -1)
	{
		ft_putstr_fd(MSG_PREFIX, 2);
		ft_putstr_fd(dist, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		fd = -1;
	}
	else if (access(dist, R_OK) == 0)
		fd = open(dist, O_RDONLY);
	return (fd);
}
