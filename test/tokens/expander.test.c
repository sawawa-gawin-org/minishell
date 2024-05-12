/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:59:00 by saraki            #+#    #+#             */
/*   Updated: 2024/05/07 20:15:18 by saraki           ###   ########.fr       */
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
	t_blst	*t_lst;
	t_blst	*e_lst;
	
	e_lst = (t_blst *)init_env();
	t_lst = commandStringToList(str);
	if (t_lst == NULL)
		return (NULL);
	expander(&t_lst, &e_lst);
	dealocateList(&t_lst);
	return ("");
}
