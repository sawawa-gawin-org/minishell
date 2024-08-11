/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:52:14 by syamasaw          #+#    #+#             */
/*   Updated: 2024/02/29 15:36:16 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

extern volatile sig_atomic_t	g_signal;

# define OK 0
# define CONTINUE -1
# define ERR -2
# define EXIT_CALLED -3

typedef struct s_sig
{
	int	interrupt;
}		t_sig;

int		add_history_wraper(
			char *line, char *heredoc_gained_str);

void	init_readline(void);
void	init_signal(void (*handler_for_sigint)(int), \
	void (*handler_for_sigquit)(int));
void	set_signal(int signum, void (*handler)(int), int flags);
void	handler_for_outer_readline(int signum);

#endif