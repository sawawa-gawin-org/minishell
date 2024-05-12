/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:42:06 by saraki            #+#    #+#             */
/*   Updated: 2024/03/01 15:01:39 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_test.h"

// Avoid err `more undefined references to `g_signal' follow`
#include <signal.h>
volatile sig_atomic_t	g_signal = 0;

static char	*test(char *str);

int	main()
{
	char *cmd[] = {
		"ls -la",
		"ls -la | wc -l",
		"ls -la | wc -l | wc -l",
		"ls -la | wc -l | wc -l | wc -l",
		"ls -la | wc -l | wc -l | wc -l | wc -l",
		"ls -la | wc -l | wc -l | wc -l | wc -l | wc -l",
		"ls -la | wc -l | wc -l | wc -l | wc -l | wc -l | wc -l",
		"ls -la | wc -l | wc -l | wc -l | wc -l | wc -l | wc -l | wc -l",
		"ls -la | wc -l | wc -l | wc -l | wc -l | wc -l | wc -l | wc -l | wc -l",
		"ls -la",
		NULL
	};
	int i = 0;
	while (cmd[i] != NULL)
	{
		printf("input: \"%s\"\nresult: %s", cmd[i], test(cmd[i]));
		i ++;
	}
	return (0);
}

static char	*test(char *str)
{
	t_blst	*lst;

	lst = commandStringToList(str);
	if (lst == NULL)
		return (NULL);
	parser(&lst);
	dealocateList(&lst);
	return ("");
}
