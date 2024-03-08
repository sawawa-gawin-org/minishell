/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_mid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:35:17 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/08 09:01:11 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_int.h"

static void	do_middle_child(char **cmd, char *path, char *envp[], t_pipex *pipe);

void	make_middle_child(char *phrase, t_pipex *pipe, char *envp[])
{
	char	**cmd;
	char	*path;
	t_pipex	*pre_pipe;
	t_pipex	*next_pipe;

	cmd = ft_split(phrase, ' ');
	if (cmd == NULL)
		return (1);
	path = find_cmd(cmd[0], envp);
	if (!path)
	{
		free_split(cmd);
		return (1);
	}
	pre_pipe = (t_pipex *) &(pipe->head)[pipe->index - 1];
	next_pipe = (t_pipex *) &(pipe->head)[pipe->index + 1];
	pipe_fds(&pre_pipe->pipe_out_fd, &pipe->pipe_in_fd);
	pipe_fds(&pipe->pipe_out_fd, &next_pipe->pipe_in_fd);
	pipe->pids = fork();
	if (pipe->pids == 0)
		do_middle_child(cmd, path, envp, pipe);
	free_split(cmd);
	free(path);
	if (next_pipe->pids < 0)
		return (1);
	return (0);
}

static void	do_middle_child(char **cmd, char *path, char *envp[], t_pipex *pipe)
{
	dup2(pipe->pipe_out_fd, STDIN_FILENO);
	dup2(pipe->pipe_in_fd, STDOUT_FILENO);
	execve(path, cmd, envp);
}
