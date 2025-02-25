/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 07:06:33 by syamasaw          #+#    #+#             */
/*   Updated: 2025/02/25 14:20:56 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	triggerd_event_in_prompt(void);
static int	triggerd_event_in_heredoc(void);

void	init_rl_for_prompt(void)
{
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
