/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:30:34 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 15:27:45 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"

static int	valid_option(char **cmd);

/**
 * Executes the built-in command "env".
 *
 * This function takes an array of command arguments `cmd` and a pointer to a
 * linked list `envlst` representing the environment variables. It executes the
 * "env" command, which prints the current environment variables to the standard
 * output.
 *
 * @param cmd     The array of command arguments.
 * @param envlst  A pointer to the linked list representing the environment
 * variables.
 * @return        Returns 0 on success, or a non-zero value on failure.
 */
int	builtin_env(char **cmd, t_blst **envlst, int mode)
{
	int		status;

	if (mode == IS_MAIN_PROCESS)
		return (OK);
	status = valid_option(cmd);
	if (status > 0)
		return (status);
	print_env(*envlst);
	return (OK);
}

static int	valid_option(char **cmd)
{
	if (cmd[1] != NULL)
	{
		env_err();
		return (MISUSE_OF_SHELL_BUILTINS);
	}
	return (OK);
}
