/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:47:48 by saraki            #+#    #+#             */
/*   Updated: 2024/04/04 16:07:30 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "libft.h"

static int	init_pipeline(t_blst *pipe_head_node);
static int	wait_processes(t_blst *pipe_head_node);
static int	make_process(char *phrase, t_pipex *pipe, t_callback callback);

int	make_processes(t_blst *token_head_node, t_blst *pipe_head_node)
{
	int		err;

	err = 0;
	if (init_pipeline(pipe_head_node))
		return (ERR);
	while (pipe_head_node->data != NULL)
	{
		if (pipe_head_node->prev->data == NULL)
			err = make_process(units[i], &pipe_arr[i], do_first_process);
		else if (pipe_head_node->next->data == NULL)
			err = make_process(units[i], &pipe_arr[i], do_last_process);
		else
			err = make_process(units[i], &pipe_arr[i], do_middle_process);
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

// TODO next
static int	make_process(char *phrase, t_pipex *pipe, t_callback callback)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(phrase, ' ');
	if (cmd == NULL)
		return (1);
	path = find_cmd(cmd[0], environ);
	if (!path)
		return (free_split(cmd, 1));
	pipe->pids = fork();
	if (pipe->pids == 0)
		callback(cmd, path, pipe);
	free_split(cmd, 0);
	free(path);
	if (pipe->pids < 0)
		return (1);
	return (0);
}