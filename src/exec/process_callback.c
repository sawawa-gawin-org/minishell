/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_callback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:43:11 by saraki            #+#    #+#             */
/*   Updated: 2024/06/30 02:00:56 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static void	close_fds_in_processes(t_blst *pipe_head_node, int index);

//  pre-process  ______________  next-process
//  pipe_in_fd ->     pipe     -> pipe_out_fd
//               ‾‾‾‾‾‾‾‾‾‾‾‾‾‾
void	do_first_process(t_callback_parametors *params)
{
	close_fds_in_processes(params->pipe->head_node, params->pipe->index);
	if (params->status != 0)
		exit(params->status);
	dup2(params->pipe->pipe_in_fd, STDOUT_FILENO);
	if (params->pipe->file_in_fd >= 0)
		dup2(params->pipe->file_in_fd, STDIN_FILENO);
	if (params->pipe->file_out_fd >= 0)
	{
		close(params->pipe->pipe_in_fd);
		dup2(params->pipe->file_out_fd, STDOUT_FILENO);
	}
	if (is_builtin(params->cmd[0]))
		exit(exec_builtin(params->cmd, params->env_lst));
	execve(params->path, params->cmd, params->env);
}

void	do_middle_process(t_callback_parametors *params)
{
	if (params->status != 0)
		exit(params->status);
	dup2(params->pipe->pipe_out_fd, STDIN_FILENO);
	if (params->pipe->file_in_fd >= 0)
	{
		close(params->pipe->pipe_out_fd);
		dup2(params->pipe->file_in_fd, STDIN_FILENO);
	}
	close_fds_in_processes(params->pipe->head_node, params->pipe->index);
	dup2(params->pipe->pipe_in_fd, STDOUT_FILENO);
	if (params->pipe->file_out_fd >= 0)
	{
		close(params->pipe->pipe_in_fd);
		dup2(params->pipe->file_out_fd, STDOUT_FILENO);
	}
	if (is_builtin(params->cmd[0]))
		exit(exec_builtin(params->cmd, params->env_lst));
	execve(params->path, params->cmd, params->env);
}

void	do_last_process(t_callback_parametors *params)
{
	close_fds_in_processes(params->pipe->head_node, params->pipe->index);
	if (params->status != 0)
		exit(params->status);
	dup2(params->pipe->pipe_out_fd, STDIN_FILENO);
	if (params->pipe->file_in_fd >= 0)
	{
		close(params->pipe->pipe_out_fd);
		dup2(params->pipe->file_in_fd, STDIN_FILENO);
	}
	if (params->pipe->file_out_fd >= 0)
		dup2(params->pipe->file_out_fd, STDOUT_FILENO);
	if (is_builtin(params->cmd[0]))
		exit(exec_builtin(params->cmd, params->env_lst));
	execve(params->path, params->cmd, params->env);
}

static void	close_fds_in_processes(t_blst *pipe_head_node, int index)
{
	t_pipex	*pipe;
	int		i;

	i = 0;
	while (pipe_head_node->u_data.pipe_data != NULL)
	{
		if (i == index)
		{
			i ++;
			pipe_head_node = pipe_head_node->next;
			continue ;
		}
		pipe = (t_pipex *) pipe_head_node->u_data.pipe_data;
		if (pipe->pipe_in_fd >= 0)
			close(pipe->pipe_in_fd);
		if (pipe->pipe_out_fd >= 0)
			close(pipe->pipe_out_fd);
		i ++;
		pipe_head_node = pipe_head_node->next;
	}
	return ;
}
