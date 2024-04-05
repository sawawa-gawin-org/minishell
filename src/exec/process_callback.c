/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_callback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:43:11 by saraki            #+#    #+#             */
/*   Updated: 2024/04/05 03:43:21 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

void	do_first_process(char **cmd, char *path, t_pipex *pipe)
{
	close_fds_in_child(pipe->head_node, pipe->index);
	dup2(pipe->pipe_in_fd, STDOUT_FILENO);
	execve(path, cmd, environ);
}

void	do_middle_process(char **cmd, char *path, t_pipex *pipe)
{
	dup2(pipe->pipe_out_fd, STDIN_FILENO);
	close_fds_in_child(pipe->head_node, pipe->index);
	dup2(pipe->pipe_in_fd, STDOUT_FILENO);
	execve(path, cmd, environ);
}

void	do_last_process(char **cmd, char *path, t_pipex *pipe)
{
	close_fds_in_child(pipe->head_node, pipe->index);
	dup2(pipe->pipe_out_fd, STDIN_FILENO);
	execve(path, cmd, environ);