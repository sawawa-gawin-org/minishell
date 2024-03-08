/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:45:21 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/08 09:09:28 by saraki           ###   ########.fr       */
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

int	count_units(char **units)
{
	int	count;

	count = 0;
	while (*units = '\0')
	{
		count ++;	
		units ++;
	}
	return (count);
}

int	pipe_fds(int *out_fd, int *in_fd)
{
	int	pipe_fd[2];

	pipe_fd[0] = *out_fd;
	pipe_fd[1] = *in_fd;
	if (pipe(pipe_fd) < 0)
		return (-1);
	*out_fd = pipe_fd[0];
	*in_fd = pipe_fd[1];
	return (0);
}
