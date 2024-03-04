/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:35:17 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/01 17:44:11 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static void	do_child_2(char **cmd, char *path, char *envp[], t_pipex *pipex);

void	make_child_2(char *arg, char *envp[], t_pipex *pipex)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(arg, ' ');
	if (!cmd)
		exit_closepipe(pipex);
	path = find_cmd(cmd[0], envp);
	if (!path)
	{
		free_split(cmd);
		exit_closepipe(pipex);
	}
	pipex->pids[1] = fork();
	if (pipex->pids[1] == 0)
		do_child_2(cmd, path, envp, pipex);
	free_split(cmd);
	free(path);
	if (pipex->pids[1] < 0)
		exit_closepipe(pipex);
}

static void	do_child_2(char **cmd, char *path, char *envp[], t_pipex *pipex)
{
	dup2(pipex->pipe_fds[0], STDIN_FILENO);
	close(pipex->pipe_fds[1]);
	dup2(pipex->io_fds[1], STDOUT_FILENO);
	execve(path, cmd, envp);
}
