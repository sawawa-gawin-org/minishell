/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:31:40 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/20 16:48:04 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal(int signum, void handler(int), struct sigaction *sa)
{
	sa->sa_flags = SA_RESTART;
	sa->sa_handler = handler;
	sigemptyset(&(sa->sa_mask));
	sigaction(signum, sa, NULL);
}
