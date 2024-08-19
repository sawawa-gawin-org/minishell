/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_err_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:24:32 by saraki            #+#    #+#             */
/*   Updated: 2024/08/07 02:26:46 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	env_err(char *cmd)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": options and arguments are not allowed\n", 2);
	return (MISUSE_OF_SHELL_BUILTINS);
}
