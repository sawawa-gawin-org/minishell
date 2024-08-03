/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:56:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/03 09:13:10 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"

/**
 * Checks if a command is a built-in command.
 *
 * @param cmd The command to check.
 * @return 1 if the command is a built-in command, 0 otherwise.
 */
int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

/**
 * Executes a built-in command.
 *
 * This function takes a command and a linked list of environment variables,
 * and executes the corresponding built-in command based on the command name.
 *
 * @param cmd The command to be executed.
 * @param envlst The linked list of environment variables.
 * @param mode When this function is called in the main process,
 * mode is `IS_MAIN_PROCESS`. When this function is called in a child
 * process, mode is `IS_CHILD_PROCESS`.
 * @return The exit status of the built-in command.
 */
int	call_builtin(char **cmd, t_blst **envlst, int mode)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (builtin_echo(cmd, envlst, mode));
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd, envlst, mode));
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd(cmd, envlst, mode));
	if (ft_strcmp(cmd[0], "export") == 0)
		return (builtin_export(cmd, envlst, mode));
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (builtin_unset(cmd, envlst, mode));
	if (ft_strcmp(cmd[0], "env") == 0)
		return (builtin_env(cmd, envlst, mode));
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (builtin_exit(cmd, envlst, mode));
	return (CMD_NOT_FOUND);
}
