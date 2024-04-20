/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:33:56 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/20 19:58:56 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static void	get_heredoc_input(char *delimiter, int *pipefd);
static void	handle_heredoc(int sig);
static int	hook_sigint(void);

//fd = heredoc_get(char *delimiter);
int	heredoc_get(char *delimiter, t_init_data *init_data)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		return (-1);
	set_signal(SIGINT, SIG_IGN, &init_data->sa);
	pid = fork();
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	else if (pid == 0)
	{
		set_signal(SIGINT, handle_heredoc, &init_data->sa);
		rl_event_hook = hook_sigint;
		get_heredoc_input(delimiter, pipefd);
	}
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	set_signal(SIGINT, sig_handler, &init_data->sa);
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
			write(1, "> ", 2);
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

static void	handle_heredoc(int sig)
{
	g_signal = sig;
}

static int	hook_sigint(void)
{
	if (g_signal == SIGINT)
	{
		rl_event_hook = 0;
		write(1, "\n", 1);
		rl_done = 1;
	}
	return (0);
}
