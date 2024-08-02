/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:14:12 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 18:42:12 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"

static int	exit_status_handling(char **cmd);

int	builtin_exit(char **cmd, t_blst **envlst, int mode)
{
	(void) envlst;
	if (mode == IS_MAIN_PROCESS)
		ft_putstr_fd("exit\n", 2);
	return (exit_status_handling(cmd));
}

static int	exit_status_handling(char **cmd)
{
	size_t	status;
	int		flag;

	status = 0;
	if (cmd[1] == NULL)
		return ((int) status);
	else if (cmd[2] == NULL)
		flag = parse_str_to_numeric(cmd[1], &status);
	else
	{
		exit_argc_err(); // dont exit terminal
		return (GENERAL_ERR);
	}
	if (flag > 0)
	{
		exit_numeric_err(cmd[1]);
		return (MISUSE_OF_SHELL_BUILTINS); // exit terminal
	}
	return ((int)(status % 256));
}
