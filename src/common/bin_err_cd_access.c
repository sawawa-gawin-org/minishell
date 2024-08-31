/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_err_cd_access.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:47:21 by saraki            #+#    #+#             */
/*   Updated: 2024/08/31 22:19:39 by saraki           ###   ########.fr       */
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
