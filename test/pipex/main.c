/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:41:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/02 15:49:08 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static void	init_struct(t_pipex *pipex);
static void	open_io_files(int argc, char *argv[], t_pipex *pipex);

int	main(int argc, char *argv[], char *envp[])
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

// int	main(int argc, char *argv[])
// {
// 	int pipefd[2];
// 	pid_t cpid;
// 	char buf;

// 	if (argc != 2) {
// 		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pipe(pipefd) == -1) {
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}

// 	cpid = fork();
// 	if (cpid == -1) {
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (cpid == 0) {    /* Child reads from pipe */
// 		close(pipefd[1]);          /* Close unused write end */

// 		while (read(pipefd[0], &buf, 1) > 0)
// 			write(STDOUT_FILENO, &buf, 1);

// 		write(STDOUT_FILENO, "\n", 1);
// 		close(pipefd[0]);
// 		_exit(EXIT_SUCCESS);

// 	} else {            /* Parent writes argv[1] to pipe */
// 		close(pipefd[0]);          /* Close unused read end */
// 		write(pipefd[1], argv[1], strlen(argv[1]));
// 		close(pipefd[1]);          /* Reader will see EOF */
// 		wait(NULL);                /* Wait for child */
// 		exit(EXIT_SUCCESS);
// 	}
// }
