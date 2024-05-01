/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:33:56 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/01 14:47:40 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_int.h"

static void	get_heredoc_input(char *delimiter, int *pipefd);

//fd = heredoc_get(char *delimiter);
int	heredoc_get(char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	else if (pid == 0)
		get_heredoc_input(delimiter, pipefd);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	if (g_signal != 0)
	{
		close(pipefd[0]);
		g_signal = 0;
		return (-1);
	}
	return (pipefd[0]);
}

static void	get_heredoc_input(char *delimiter, int *pipefd)
{
	char	*line;

	close(pipefd[0]);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || g_signal != 0)
		{
			break ;
		}
		else if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipefd[1]);
		ft_putstr_fd("\n", pipefd[1]);
		free(line);
	}
	ft_putstr_fd("\0", pipefd[1]);
	close(pipefd[1]);
	exit(0);
}
