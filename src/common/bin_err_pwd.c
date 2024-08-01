/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_err_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:40:52 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 14:42:59 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	pwd_err(char *str)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("pwd: ", 2);
	ft_putchar_fd(str[0], 2);
	ft_putchar_fd(str[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (GENERAL_ERR);
}
