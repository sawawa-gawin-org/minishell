/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_old.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:50:46 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/09 10:08:17 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static void	do_oldest_child(char **cmd, char *path, char *envp[], t_pipex *pipe);

int	make_oldest_child(char *phrase, t_pipex *pipe, char *envp[])
{
	char	**cmd;
	char	*path;
	t_pipex	*next_pipe;

	cmd = ft_split(phrase, ' ');
	if (cmd == NULL)
		return (1);
	path = find_cmd(cmd[0], envp);
	if (!path)
		return (free_split(cmd, 1));
	next_pipe = &((t_pipex *) (pipe->head))[pipe->index + 1];
	pipe_fds(&next_pipe->pipe_out_fd, &pipe->pipe_in_fd);
	pipe->pids = fork();
	if (pipe->pids == 0)
		do_oldest_child(cmd, path, envp, pipe);
	free_split(cmd, 0);
	free(path);
	if (next_pipe->pids < 0)
		return (1);
	return (0);
}

static void	do_oldest_child(char **cmd, char *path, char *envp[], t_pipex *pipe)
{
	dup2(pipe->pipe_in_fd, STDOUT_FILENO);
	close(pipe->pipe_out_fd);
	// dup2(pipe->in_fd, STDIN_FILENO);
	execve(path, cmd, envp);
}
