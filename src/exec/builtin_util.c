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
