/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:47:48 by saraki            #+#    #+#             */
/*   Updated: 2024/05/15 07:22:00 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "libft.h"

static int	init_pipeline(t_blst *pipe_node);
static int	pipe_fds(int *out_fd, int *in_fd);
static int	wait_processes(t_blst *pipe_node);

int	make_processes(t_tokenlst *token_node, t_pipelst *pipe_node)
{
	int			err;
	t_pipelst	*pipe_head_node;

	err = 0;
	if (init_pipeline(pipe_node))
		return (ERR);
	pipe_head_node = pipe_node;
	while (pipe_node->u_data.pipe_data != NULL)
	{
		if (pipe_node->prev->u_data.pipe_data == NULL)
			err = make_process(token_node, pipe_node, do_first_process);
		else if (pipe_node->next->u_data.pipe_data == NULL)
			err = make_process(token_node, pipe_node, do_last_process);
		else
			err = make_process(token_node, pipe_node, do_middle_process);
		if (err != 0)
			return (wait_processes(pipe_head_node));
		pipe_node = pipe_node->next;
	}
	return (wait_processes(pipe_head_node));
}

static int	init_pipeline(t_pipelst *pipe_node)
{
	t_pipex	*pipe;
	t_pipex	*next_pipe;

	while (pipe_node->u_data.pipe_data != NULL)
	{
		pipe = (t_pipex *) pipe_node->u_data.pipe_data;
		if (pipe_node->next->u_data.pipe_data != NULL)
		{
			next_pipe = pipe_node->next->u_data.pipe_data;
			if (pipe_fds(&next_pipe->pipe_out_fd, &pipe->pipe_in_fd))
				return (ERR);
		}
		pipe_node = pipe_node->next;
	}
	return (OK);
}

static int	pipe_fds(int *out_fd, int *in_fd)
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

static int	wait_processes(t_pipelst *pipe_node)
{
	t_pipex	*now_pipe;
	t_pipex	*pre_pipe;

	while (pipe_node->u_data.pipe_data != NULL)
	{
		if (pipe_node->prev->u_data.pipe_data != NULL)
		{
			pre_pipe = (t_pipex *)pipe_node->prev->u_data.pipe_data;
			close(pre_pipe->pipe_in_fd);
			close(pre_pipe->pipe_out_fd);
			pre_pipe->pipe_in_fd = -1;
		}
		now_pipe = (t_pipex *)pipe_node->u_data.pipe_data;
		if (waitpid(now_pipe->pids, NULL, 0) == -1)
			return (ERR);
		pipe_node = pipe_node->next;
	}
	return (OK);
}
