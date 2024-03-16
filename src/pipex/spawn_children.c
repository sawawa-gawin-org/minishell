/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 05:22:42 by saraki            #+#    #+#             */
/*   Updated: 2024/03/16 17:54:19 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

/* 
- make_*_child関数の中でファイルの展開を行う
*/
static int	init_pipeline(t_pipex *pipe_arr, int size);
static int	wait_processes(t_pipex *pipe_arr, int size);

int	spawn_children(char **units, int size, t_pipex *pipe_arr, char **envp)
{
	int		i;
	int		err;

	i = 0;
	err = 0;
	if (init_pipeline(pipe_arr, size))
		return (ERR);
	while (i < size)
	{
		if (i == 0)
			err = make_oldest_child(units[i], &pipe_arr[i], envp);
		else if (i == size - 1)
			err = make_youngest_child(units[i], &pipe_arr[i], envp);
		else
			err = make_middle_child(units[i], &pipe_arr[i], envp);
		if (err != 0)
			return (ERR); // TODO:waitpid
		i ++;
	}
	return (wait_processes(pipe_arr, size));
}

static int	init_pipeline(t_pipex *pipe_arr, int size)
{
	t_pipex	*pipe;
	t_pipex	*next_pipe;
	int		i;

	i = 0;
	while (i < size)
	{
		pipe = &pipe_arr[i];
		if (i != size - 1)
		{
			next_pipe = &((t_pipex *) (pipe->head))[i + 1];
			if (pipe_fds(&next_pipe->pipe_out_fd, &pipe->pipe_in_fd))
				return (ERR);
		}
		i ++;
	}
	return (OK);
}

static int	wait_processes(t_pipex *pipe_arr, int size)
{
	int		i;
	pid_t 	err;

	i = 0;
	while (i < size)
	{
		err = waitpid(pipe_arr[i].pids, NULL, 0);
		i ++;
	}
	if (err)
		return (ERR);
	return (OK);
}
