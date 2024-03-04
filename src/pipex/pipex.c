/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:03:48 by saraki            #+#    #+#             */
/*   Updated: 2024/03/04 17:05:23 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static void	init_struct(t_pipex *pipex);
static void	open_io_files(int argc, char *argv[], t_pipex *pipex);

int	pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	init_struct(&pipex);
	open_io_files(argc, argv, &pipex);
	if (pipe(pipex.pipe_fds) < 0)
		exit(close_fd(pipex.io_fds, 1));
	make_child_1(argv[2], envp, &pipex);
	make_child_2(argv[3], envp, &pipex);
	close_fd(pipex.pipe_fds, 0);
	waitpid(pipex.pids[0], NULL, 0);
	waitpid(pipex.pids[1], NULL, 0);
	return (0);
}

static void	init_struct(t_pipex *pipex)
{
	pipex->io_fds[0] = -1;
	pipex->io_fds[1] = -1;
	pipex->pipe_fds[0] = -1;
	pipex->pipe_fds[1] = -1;
	pipex->pids[0] = 0;
	pipex->pids[1] = 0;
}

static void	open_io_files(int argc, char *argv[], t_pipex *pipex)
{
	if (argv[argc - 1] && access(argv[argc - 1], F_OK) == -1)
		pipex->io_fds[1] = open(argv[argc - 1], O_CREAT | O_WRONLY, \
			S_IREAD | S_IWRITE);
	else if (argv[argc - 1] && access(argv[argc - 1], F_OK) == 0)
		pipex->io_fds[1] = open(argv[argc - 1], O_WRONLY);
	if (pipex->io_fds[1] == -1)
		exit(close_fd(pipex->io_fds, 1));
	if (argv[1] && access(argv[1], R_OK) == 0)
		pipex->io_fds[0] = open(argv[1], O_RDONLY);
	if (pipex->io_fds[0] == -1)
		exit(close_fd(pipex->io_fds, 1));
	if (argc != 5 || ft_strlen(argv[2]) <= 0 || ft_strlen(argv[3]) <= 0)
		exit(close_fd(pipex->io_fds, 1));
}
