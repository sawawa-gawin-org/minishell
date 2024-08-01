/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_err_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:40:52 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 17:09:05 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	exit_numeric_err(char *str)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (GENERAL_ERR);
}

int	exit_argc_err(void)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd("too many arguments\n", 2);
	return (GENERAL_ERR);
}
