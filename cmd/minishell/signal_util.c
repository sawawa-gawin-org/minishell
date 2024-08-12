/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:31:40 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/01 15:57:08 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signal(void (*handler_for_sigint)(int), \
	void (*handler_for_sigquit)(int))
{
	set_signal(SIGINT, handler_for_sigint, 0);
	set_signal(SIGQUIT, handler_for_sigquit, 0);
}

void	set_signal(int signum, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = flags;
	sa.sa_handler = handler;
	sigaction(signum, &sa, NULL);
}

void	handler_for_outer_readline(int signum)
{
	if (signum == SIGINT)
		g_signal = SIGINT;
}

void	handler_for_heredoc_readline(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		rl_done = 1;
	}
}
