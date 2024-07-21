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
