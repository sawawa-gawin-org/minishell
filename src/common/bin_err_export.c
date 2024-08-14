/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_err_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:24:32 by saraki            #+#    #+#             */
/*   Updated: 2024/08/14 07:33:07 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	export_option_err(char flag_char)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("export: -", 2);
	ft_putchar_fd(flag_char, 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (GENERAL_ERR);
}

int	export_identifier_err(char *str)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (GENERAL_ERR);
}
