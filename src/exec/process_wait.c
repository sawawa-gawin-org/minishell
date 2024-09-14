/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 08:56:58 by saraki            #+#    #+#             */
/*   Updated: 2024/09/14 12:01:40 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static int	cmp_pid(void *data, void *query_pt);
static void	close_pipe_fds(t_pipelst *pipe_node);
static int	check_status(int status);

int	wait_processes(t_pipelst *pipe_node)
{
	int			status;
	pid_t		exited_pid;
	t_pipelst	*exited_node;
	int			err;

	status = OK;
	err = 0;
	close_pipe_fds(pipe_node);
	while (pipe_node->u_data.pipe_data != NULL)
	{
		exited_pid = waitpid(-1, &status, 0);
		if (exited_pid == -1)
			err = GENERAL_ERR;
		exited_node = (t_pipelst *)doub_lstsearch(
				pipe_node->u_data.pipe_data->head_node, &exited_pid, cmp_pid);
		if (exited_node->u_data.pipe_data != NULL)
			exited_node->u_data.pipe_data->exit_status = status;
		else
			err = GENERAL_ERR;
		pipe_node = pipe_node->next;
	}
	if (err != 0)
		return (err);
	return (check_status(pipe_node->prev->u_data.pipe_data->exit_status));
}

static int	cmp_pid(void *data, void *query_pt)
{
	pid_t		*pid;
	t_pipex		*pipe_data;

	pid = (pid_t *)query_pt;
	pipe_data = (t_pipex *)data;
	if (pipe_data->pids == *pid)
		return (1);
	return (0);
}

static void	close_pipe_fds(t_pipelst *pipe_node)
{
	t_pipex		*pre_pipe_data;
	t_pipex		*now_pipe_data;

	while (pipe_node->u_data.pipe_data != NULL)
	{
		now_pipe_data = pipe_node->u_data.pipe_data;
		if (pipe_node->prev->u_data.pipe_data != NULL)
		{
			pre_pipe_data = (t_pipex *)pipe_node->prev->u_data.pipe_data;
			close(pre_pipe_data->pipe_in_fd);
			close(now_pipe_data->pipe_out_fd);
			pre_pipe_data->pipe_in_fd = -1;
			now_pipe_data->pipe_out_fd = -1;
		}
		pipe_node = pipe_node->next;
	}
	return ;
}

static int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit", 2);
		ft_putstr_fd("\n", 2);
		return (WTERMSIG(status) + 128);
	}
	return (GENERAL_ERR);
}
