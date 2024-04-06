/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_callback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:43:11 by saraki            #+#    #+#             */
/*   Updated: 2024/04/06 04:51:21 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static void	close_fds_in_processes(t_blst *pipe_head_node, int index);

void	do_first_process(char **cmd, char *path, t_pipex *pipe)
{
	close_fds_in_processes(pipe->head_node, pipe->index);
	dup2(pipe->pipe_in_fd, STDOUT_FILENO);
	execve(path, cmd, environ);
}

void	do_middle_process(char **cmd, char *path, t_pipex *pipe)
{
	dup2(pipe->pipe_out_fd, STDIN_FILENO);
	close_fds_in_processes(pipe->head_node, pipe->index);
	dup2(pipe->pipe_in_fd, STDOUT_FILENO);
	execve(path, cmd, environ);
}

void	do_last_process(char **cmd, char *path, t_pipex *pipe)
{
	close_fds_in_processes(pipe->head_node, pipe->index);
	dup2(pipe->pipe_out_fd, STDIN_FILENO);
	execve(path, cmd, environ);
}

static void	close_fds_in_processes(t_blst *pipe_head_node, int index)
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
			continue ;
		}
		pipe = (t_pipex *) pipe_head_node->data;
		if (pipe->pipe_in_fd >= 0)
			close(pipe->pipe_in_fd);
		if (pipe->pipe_out_fd >= 0)
			close(pipe->pipe_out_fd);
		i ++;
		pipe_head_node = pipe_head_node->next;
	}
	return ;
}
