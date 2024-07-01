/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:47:48 by saraki            #+#    #+#             */
/*   Updated: 2024/06/30 02:00:44 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "libft.h"

static int	init_pipeline(t_blst *pipe_node);
static int	pipe_fds(int *out_fd, int *in_fd);
static int	wait_processes(t_pipelst *pipe_node);

int	make_processes(t_exec_parametors *param)
{
	int			err;
	t_pipelst	*pipe_head_node;
	t_pipelst	*current_pipe_node;

	err = 0;
	if (init_pipeline(param->pipe_list))
		return (GENERAL_ERR);
	pipe_head_node = param->pipe_list;
	current_pipe_node = param->pipe_list;
	while (current_pipe_node->u_data.pipe_data != NULL)
	{
		if (current_pipe_node->prev->u_data.pipe_data == NULL)
			err = make_process(param, do_first_process);
		else if (current_pipe_node->next->u_data.pipe_data == NULL)
			err = make_process(param, do_last_process);
		else
			err = make_process(param, do_middle_process);
		if (err != 0)
			return (wait_processes(pipe_head_node));
		current_pipe_node = current_pipe_node->next;
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
	int		status;
	int		err;

	status = OK;
	err = 0;
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
		if (waitpid(now_pipe->pids, &status, 0) == -1)
			err = GENERAL_ERR;
		pipe_node = pipe_node->next;
	}
	if (err != 0)
		return (err);
	return (WEXITSTATUS(status));
}
