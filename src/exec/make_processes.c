/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:47:48 by saraki            #+#    #+#             */
/*   Updated: 2024/04/03 19:06:54 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "libft.h"

static int	init_pipeline(t_blst *pipe_head_node);
static int	wait_processes(t_blst *pipe_head_node);

int	make_processes(t_blst *token_head_node, t_blst *pipe_head_node)
{
	int		err;

	err = 0;
	if (init_pipeline(pipe_head_node))
		return (ERR);
	while (pipe_head_node->data != NULL)
	{
		if (pipe_head_node->prev->data == NULL)
			err = make_oldest_child(units[i], &pipe_arr[i], envp);
		else if (pipe_head_node->next->data == NULL)
			err = make_youngest_child(units[i], &pipe_arr[i], envp);
		else
			err = make_middle_child(units[i], &pipe_arr[i], envp);
		if (err != 0)
			return (ERR); // TODO:waitpid
		pipe_head_node = pipe_head_node->next;
	}
	return (wait_processes(pipe_head_node));
}

static int	init_pipeline(t_blst *pipe_head_node)
{
	t_pipex	*pipe;
	t_pipex	*next_pipe;
	t_blst	*sentinel;

	while (pipe_head_node->data != NULL)
	{
		pipe = (t_pipex	*) pipe_head_node->data;
		if (pipe_head_node->next->data != NULL)
		{
			next_pipe = pipe_head_node->next->data;
			if (pipe_fds(&next_pipe->pipe_out_fd, &pipe->pipe_in_fd))
				return (ERR);
		}
		pipe_head_node = pipe_head_node->next;
	}
	return (OK);
}

static int	wait_processes(t_blst *pipe_head_node)
{
	t_pipex	*now_pipe;
	t_pipex	*pre_pipe;
	int		index;

	while (pipe_head_node->data != NULL)
	{
		if (pipe_head_node->prev->data != NULL)
		{
			pre_pipe = (t_pipex *)pipe_head_node->prev->data;
			close(pre_pipe->pipe_in_fd);
			close(pre_pipe->pipe_out_fd);
			pre_pipe->pipe_in_fd = -1;
		}
		now_pipe = (t_pipex *)pipe_head_node->data;
		if (waitpid(now_pipe->pids, NULL, 0) == -1)
			printf("waitpid error\n");
		pipe_head_node = pipe_head_node->next;
	}
	return (OK);
}
