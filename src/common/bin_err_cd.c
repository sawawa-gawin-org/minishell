/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_err_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:47:21 by saraki            #+#    #+#             */
/*   Updated: 2024/09/14 14:57:51 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	cd_argc_err(void)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd("too many arguments\n", 2);
	return (GENERAL_ERR);
}

int	cd_option_err(char *cmd)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (MISUSE_OF_SHELL_BUILTINS);
}

int	cd_unimplemented_option_err(char *cmd)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": [-L|[-P [-e]] [-@]] are not implemented\n", 2);
	return (MISUSE_OF_SHELL_BUILTINS);
}

int	cd_cwd_error(void)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd("error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
	return (GENERAL_ERR);
}
