/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:45:21 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/05 03:40:45 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_int.h"

int	close_fd(int *fds, int exit_code)
{
	if (fds[0] >= 0)
		close(fds[0]);
	if (fds[1] >= 0)
		close(fds[1]);
	return (exit_code);
}

void	free_split(char **s)
{
	int	i;

	i = -1;
	while (s[++i] != NULL)
		free(s[i]);
	free(s);
}

void	exit_closepipe(t_pipex *pipex)
{
	close_fd(pipex->pipe_fds, 0);
	exit(close_fd(pipex->io_fds, 1));
}
