/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:03:48 by saraki            #+#    #+#             */
/*   Updated: 2024/03/08 09:54:54 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static t_pipex	*init_struct(int size);
static void		wait_processes(t_pipex *pipe_arr, int size);

int	pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipe_arr;
	char	**units;
	int		size;

	units = parse_argv(argc, argv);
	if (units == NULL)
		exit(1);
	size = count_units(units);
	pipe_arr = init_struct(size);
	if (pipe_arr == NULL)
	{
		free_split(units);
		exit(1);
	}
	spawn_children(units, size, pipe_arr, envp);
	wait_processes(pipe_arr, size);
	free_split(units);
	free(pipe_arr);
	return (0);
}

static t_pipex	*init_struct(int size)
{
	t_pipex	*ret;
	int		i;

	ret = ft_calloc((size_t) size, sizeof(t_pipex));
	if (ret == NULL)
		return (NULL);
	ft_memset(ret, 0, sizeof(t_pipex) * (size_t) size);
	i = 0;
	while (i < size)
	{
		ret[i].head = (void *)ret;
		ret[i].index = i;
		i ++;
	}	
	return (ret);
}

static void	wait_processes(t_pipex *pipe_arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(pipe_arr[i].pids, NULL, 0);
		i ++;
	}
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