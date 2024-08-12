/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-11 07:06:33 by syamasaw          #+#    #+#             */
/*   Updated: 2024-08-11 07:06:33 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	triggerd_event_in_prompt(void);
static int	triggerd_event_in_heredoc(void);

void	init_rl_for_prompt(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	rl_outstream = stderr;
	rl_done = 0;
	rl_catch_signals = 1;
	rl_event_hook = triggerd_event_in_prompt;
}

void	init_rl_for_heredoc(void)
{
	rl_event_hook = triggerd_event_in_heredoc;
}

static int	triggerd_event_in_heredoc(void)
{
	if (g_signal == SIGINT)
		rl_done = 0;
	return (0);
}

static int	triggerd_event_in_prompt(void)
{
	if (g_signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}
