/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-18 03:49:14 by syamasaw          #+#    #+#             */
/*   Updated: 2024-07-18 03:49:14 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static int	open_and_send_string_to_fd(char *str);

int	open_in_files(char *dist, t_pipex *pipex, int heredocflag)
{
	int	fd;

	if (dist && access(dist, R_OK) == 0 && heredocflag == 0)
		pipex->file_in_fd = open(dist, O_RDONLY);
	else if (dist && heredocflag)
	{
		fd = open_and_send_string_to_fd(dist);
		pipex->file_in_fd = fd;
	}
	if (pipex->file_in_fd == -1)
	{
		close(pipex->file_in_fd);
		close(pipex->file_out_fd);
		return (ERR);
	}
	return (OK);
}

int	open_out_files(char *dist, t_pipex *pipex, int appendflag)
{
	if (dist && access(dist, F_OK) == -1 && appendflag == 0)
		pipex->file_out_fd = open(
				dist, O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);
	else if (dist && access(dist, F_OK) == 0 && appendflag == 0)
		pipex->file_out_fd = open(dist, O_WRONLY);
	else if (dist && access(dist, F_OK) == -1 && appendflag)
		pipex->file_out_fd = open(
				dist, O_CREAT | O_WRONLY | O_APPEND, S_IREAD | S_IWRITE);
	else if (dist && access(dist, F_OK) == 0 && appendflag)
		pipex->file_out_fd = open(dist, O_WRONLY | O_APPEND);
	if (pipex->file_out_fd == -1)
	{
		close(pipex->file_in_fd);
		close(pipex->file_out_fd);
		return (ERR);
	}
	return (OK);
}

static int	open_and_send_string_to_fd(char *str)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (ERR);
	if (write(fd[1], str, ft_strlen(str)) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (ERR);
	}
	close(fd[1]);
	return (fd[0]);
}
