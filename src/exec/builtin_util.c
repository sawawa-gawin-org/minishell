/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-16 03:56:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024-07-16 03:56:27 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static int	valid_format(char *cmd);

int	is_builtin(char *cmd)
{
	// if (ft_strcmp(cmd, "echo") == 0)
	// 	return (1);
	// if (ft_strcmp(cmd, "cd") == 0)
	// 	return (1);
	// if (ft_strcmp(cmd, "pwd") == 0)
	// 	return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	// if (ft_strcmp(cmd, "unset") == 0)
	// 	return (1);
	// if (ft_strcmp(cmd, "env") == 0)
	// 	return (1);
	// if (ft_strcmp(cmd, "exit") == 0)
	// 	return (1);
	return (0);
}

char	**get_key_val(char *cmd)
{
	char	**key_val;
	int		pos;

	pos = valid_format(cmd);
	if (pos == -1)
		return (NULL);
	key_val = (char **)ft_calloc(2, sizeof(char *));
	if (key_val == NULL)
		return (NULL);
	key_val[0] = ft_substr(cmd, 0, pos);
	if (key_val[0] == NULL)
		return (NULL);
	if (cmd[pos] == '\0')
		key_val[1] = ft_strdup("");
	else
		key_val[1] = ft_strdup(cmd + pos + 1);
	if (key_val[1] == NULL)
	{
		free(key_val[0]);
		return (NULL);
	}
	return (key_val);
}

static int	valid_format(char *cmd)
{
	int	pos;

	pos = 0;
	if (cmd[0] == '\0')
		return (-1);
	if (('0' <= cmd[0] && cmd[0] <= '9') || cmd[0] == '=')
		return (-1);
	while (cmd[pos] != '\0')
	{
		if (ft_strchr("!@#-* ", cmd[pos]))
			return (-1);
		if (cmd[pos] == '=')
			break ;
		pos++;
	}
	return (pos);
}
