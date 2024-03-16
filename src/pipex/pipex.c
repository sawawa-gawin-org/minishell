/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:03:48 by saraki            #+#    #+#             */
/*   Updated: 2024/03/10 10:00:38 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static t_pipex	*init_struct(int size);

int	pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipe_arr;
	char	**units;
	int		size;
	int		err;

	units = parse_argv(argc, argv);
	if (units == NULL)
		exit(1);
	size = count_units(units);
	pipe_arr = init_struct(size);
	if (pipe_arr == NULL)
		exit(free_split(units, 1));
	err = spawn_children(units, size, pipe_arr, envp);
	close_fds(pipe_arr, size, 0);
	free_split(units, 0);
	free(pipe_arr);
	if (err)
		exit(1);
	return (0);
}

static t_pipex	*init_struct(int size)
{
	t_pipex	*ret;
	int		i;

	ret = ft_calloc((size_t) size, sizeof(t_pipex));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i].in_fd = -1;
		ret[i].out_fd = -1;
		ret[i].pipe_in_fd = -1;
		ret[i].pipe_out_fd = -1;
		ret[i].head = (void *)ret;
		ret[i].index = i;
		i ++;
	}	
	return (ret);
}

/* static void	init_struct(t_pipex *pipex)
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
 */

// #include <sys/types.h>
// #include <sys/wait.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>

// int
// main(int argc, char *argv[])
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
