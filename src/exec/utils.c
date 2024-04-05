/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:45:21 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/05 03:56:40 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

void	close_fds_in_processes(t_blst *pipe_head_node, int index)
{
	t_pipex	*pipe;
	int		i;

	i = 0;
	while (pipe_head_node->data != NULL)
	{
		if (i == index)
		{
			i ++;
			pipe_head_node = pipe_head_node->next;
			continue;
		}
		pipe = (t_pipex	*) pipe_head_node->data;
		if (pipe->pipe_in_fd >= 0)
			close(pipe->pipe_in_fd);
		if (pipe->pipe_out_fd >= 0)
			close(pipe->pipe_out_fd);
		i ++;
		pipe_head_node = pipe_head_node->next;
	}
	return ;
}

// TODO
int	close_fds_all(t_pipex *pipe_arr, int size, int exit_code)
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	u_c1;
	unsigned char	u_c2;

	i = 0;
	while (!(s1[i] == '\0' && s2[i] == '\0'))
	{
		u_c1 = (unsigned char) s1[i];
		u_c2 = (unsigned char) s2[i];
		if (u_c1 != u_c2)
			return ((int)(u_c1 - u_c2));
		i ++;
	}
	return (0);
}
