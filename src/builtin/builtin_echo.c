/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:22:59 by saraki            #+#    #+#             */
/*   Updated: 2024/08/02 16:54:01 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"
#include "libft.h"

static int	valid_option(char **cmd, int *n_flag);

int	builtin_echo(char **cmd, t_blst **envlst, int mode)
{
	int		status;
	int		n_flag;
	int		i;

	(void)envlst;
	if (mode == IS_MAIN_PROCESS)
		return (OK);
	n_flag = 0;
	i = 1;
	status = valid_option(cmd, &n_flag);
	if (status > 0)
		return (status);
	while (cmd[i] != NULL)
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		i ++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (OK);
}

static int	valid_option(char **cmd, int *n_flag)
{
	if (!cmd[1])
		return (0);
	if (ft_strcmp(cmd[1], "-n") == 0)
		*n_flag = 1;
	return (0);
}
