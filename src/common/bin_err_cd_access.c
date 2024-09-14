/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_err_cd_access.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:47:21 by saraki            #+#    #+#             */
/*   Updated: 2024/09/14 14:58:25 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	cd_no_such_file_err(char *path)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (GENERAL_ERR);
}

int	cd_not_a_directory_err(char *path)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Not a directory\n", 2);
	return (GENERAL_ERR);
}

int	cd_permission_err(char *path)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	return (GENERAL_ERR);
}

int	cd_home_not_set_err(void)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd("HOME not set\n", 2);
	return (GENERAL_ERR);
}

int	cd_oldpwd_not_set_err(void)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd("OLDPWD not set\n", 2);
	return (GENERAL_ERR);
}
