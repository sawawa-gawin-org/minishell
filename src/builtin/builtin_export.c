/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:43:28 by syamasaw          #+#    #+#             */
/*   Updated: 2024/07/21 10:41:41 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "dbllst.h"
#include "env.h"

static int	valid_option(char **cmd);

/**
 * Executes the built-in export command.
 *
 * This function takes an array of command arguments,
 *  a pointer to a linked list representing the environment variables,
 *  and a mode indicating the execution mode.
 * It performs the necessary operations to handle the export command,
 *  such as adding or modifying environment variables.
 *
 * @param cmd The array of command arguments.
 * @param envlst A pointer to the linked list representing the environment
 * variables.
 * @param mode if this function called in main process, mode is 0.
 * if this function called in child process, mode is 1.
 * @return The exit status of the command.
 */
int	builtin_export(char **cmd, t_blst **envlst, int mode)
{
	int		status;

	status = valid_option(cmd);
	if (status > 0)
		return (status);
	if ((!cmd[1] || (ft_strcmp(cmd[1], "--") == 0 && !cmd[2])))
		return (export_print(*envlst, mode));
	return (export_env(cmd, envlst, mode));
}

static int	valid_option(char **cmd)
{
	if (!cmd[1])
		return (0);
	if (cmd[1][0] == '-')
	{
		if (cmd[1][1] == '\0')
		{
			export_identifier_err("-");
			return (1);
		}
		if (cmd[1][1] != '-' || (cmd[1][1] == '-' && cmd[1][2] != '\0'))
		{
			export_option_err(cmd[1]);
			return (2);
		}
	}
	return (0);
}

int	valid_format_key(char *cmd)
{
	int	pos;

	if (!cmd || cmd[0] == '\0' || ft_isdigit(cmd[0]))
		return (-1);
	pos = 0;
	while (cmd[pos] != '\0')
	{
		if (!(ft_isalnum(cmd[pos]) || cmd[pos] == '_'))
		{
			if (pos != 0 && cmd[pos] == '=')
				break ;
			else
				return (-1);
		}
		pos++;
	}
	return (pos);
}

/**
 * Retrieves the key-value pair from the given command string
 * at the specified position.
 *
 * @param cmd The command string to extract the key-value pair from.
 * @param pos The position of the key-value pair in the command string.
 * @return A pointer to a string array containing the key-value pair.
 */
char	**get_key_val(char *cmd, int pos)
{
	char	**key_val;

	key_val = (char **)ft_calloc(2, sizeof(char *));
	if (key_val == NULL)
		return (NULL);
	key_val[0] = ft_substr(cmd, 0, pos);
	if (key_val[0] == NULL)
	{
		free(key_val);
		return (NULL);
	}
	if (cmd[pos] == '\0')
		key_val[1] = ft_strdup("");
	else
		key_val[1] = ft_strdup(cmd + pos + 1);
	if (key_val[1] == NULL)
	{
		free(key_val[0]);
		free(key_val);
		return (NULL);
	}
	return (key_val);
}

int	valid_identifier(char *cmd)
{
	int	i;

	if (!cmd || !cmd[0])
		return (-1);
	if (ft_isdigit(cmd[0]))
		return (-1);
	i = -1;
	while (cmd[++i] != '\0')
		if (!(ft_isalnum(cmd[i]) || cmd[i] == '_'))
			return (-1);
	return (0);
}
