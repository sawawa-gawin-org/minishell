/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:45:21 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/16 14:17:16 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds_in_child(t_pipex *pipe_arr, int index, int size)
{
	int		i;
	t_pipex	*pipe;

	i = 0;
	while (i < size)
	{
		if (i == index)
		{
			i ++;
			continue;
		}
		pipe = &pipe_arr[i];
		if (pipe->pipe_in_fd >= 0)
			close(pipe->pipe_in_fd);
		if (pipe->pipe_out_fd >= 0)
			close(pipe->pipe_out_fd);
		i ++;
	}
	return ;
}

int	close_fds(t_pipex *pipe_arr, int size, int exit_code)
{
	int		i;
	t_pipex	*pipe;

	i = 0;
	while (i < size)
	{
		pipe = &pipe_arr[i];
		if (pipe->in_fd >= 0)
			close(pipe->in_fd);
		if (pipe->out_fd >= 0)
			close(pipe->out_fd);
		if (pipe->pipe_in_fd >= 0)
			close(pipe->pipe_in_fd);
		if (pipe->pipe_out_fd >= 0)
			close(pipe->pipe_out_fd);
		i ++;
	}
	return (exit_code);
}

int	free_split(char **s, int exit_code)
{
	int	i;

	i = -1;
	while (s[++i] != NULL)
		free(s[i]);
	free(s);
	return (exit_code);
}

int	count_units(char **units)
{
	int	count;

	count = 0;
	while (*units != NULL)
	{
		count ++;	
		units ++;
	}
	return (count);
}

int	pipe_fds(int *out_fd, int *in_fd)
{
	int	pipe_fd[2];

	pipe_fd[0] = *out_fd;
	pipe_fd[1] = *in_fd;
	if (pipe(pipe_fd) < 0)
		return (ERR);
	*out_fd = pipe_fd[0];
	*in_fd = pipe_fd[1];
	return (OK);
}
