/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_err_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:24:32 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 13:57:11 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	env_err(void)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd("option is undefined\n", 2);
	return (GENERAL_ERR);
}
