/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:31:40 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/21 18:02:35 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int signum);
static int	check_signum(void);

void	init_signal(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	rl_outstream = stderr;
	rl_event_hook = check_signum;
	set_signal(SIGINT);
	ign_signal(SIGQUIT);
}

void	set_signal(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(signum, &sa, NULL);
}

void	ign_signal(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(signum, &sa, NULL);
}

static void	handler(int signum)
{
	g_signal = signum;
}

static int	check_signum(void)
{
	if (g_signal == 0)
		return (0);
	else if (g_signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
		return (0);
	}
	return (0);
}
