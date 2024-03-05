/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:50:46 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/05 03:41:07 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_int.h"

static void	do_child_1(char **cmd, char *path, char *envp[], t_pipex *pipex);

void	make_child_1(char *arg, char *envp[], t_pipex *pipex)
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
	pipex->pids[0] = fork();
	if (pipex->pids[0] == 0)
		do_child_1(cmd, path, envp, pipex);
	free_split(cmd);
	free(path);
	if (pipex->pids[0] < 0)
		exit_closepipe(pipex);
}

static void	do_child_1(char **cmd, char *path, char *envp[], t_pipex *pipex)
{
	dup2(pipex->pipe_fds[1], STDOUT_FILENO);
	close(pipex->pipe_fds[0]);
	dup2(pipex->io_fds[0], STDIN_FILENO);
	execve(path, cmd, envp);
}
