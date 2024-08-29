/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:47:48 by saraki            #+#    #+#             */
/*   Updated: 2024/08/29 21:13:22 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "libft.h"
#include "minishell.h"

static void	close_pipe_fds(t_pipelst *pipe_node);
static int	pipe_fds(int *out_fd, int *in_fd);
static int	check_status(int status);

int	init_pipeline(t_pipelst *pipe_node)
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

int	wait_processes(t_pipelst *pipe_node)
{
	int			status;
	int			err;
	t_pipex		*data;

	status = OK;
	err = 0;
	close_pipe_fds(pipe_node);
	while (pipe_node->u_data.pipe_data != NULL)
	{
		data = pipe_node->u_data.pipe_data;
		if (data->pids != 0 && waitpid(-1, &(data->exit_status), 0) == -1)
			err = GENERAL_ERR;
		pipe_node = pipe_node->next;
	}
	if (err != 0)
		return (err);
	status = pipe_node->next->u_data.pipe_data->exit_status;
	return (check_status(status));
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
