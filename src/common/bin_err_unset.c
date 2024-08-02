/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_err_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:49:21 by saraki            #+#    #+#             */
/*   Updated: 2024/08/02 21:50:51 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	unset_arg_err(void)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("unset: not enough arguments\n", 2);
	return (GENERAL_ERR);
}
