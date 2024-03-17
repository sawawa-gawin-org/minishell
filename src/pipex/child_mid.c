/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_mid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:35:17 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/16 14:19:45 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static void	do_middle_child(char **cmd, char *path, char *envp[], t_pipex *pipe);

int	make_middle_child(char *phrase, t_pipex *pipe, char *envp[])
{
	char	**cmd;
	char	*path;

	cmd = ft_split(phrase, ' ');
	if (cmd == NULL)
		return (1);
	path = find_cmd(cmd[0], envp);
	if (!path)
		return (free_split(cmd, 1));
	pipe->pids = fork();
	if (pipe->pids == 0)
		do_middle_child(cmd, path, envp, pipe);
	free_split(cmd, 0);
	free(path);
	if (pipe->pids < 0)
		return (1);
	return (0);
}

static void	do_middle_child(char **cmd, char *path, char *envp[], t_pipex *pipe)
{
	dup2(pipe->pipe_out_fd, STDIN_FILENO);
	close_fds_in_child(pipe->head, pipe->index, pipe->size);
	dup2(pipe->pipe_in_fd, STDOUT_FILENO);
	execve(path, cmd, envp);
}
