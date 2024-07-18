/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_err.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-18 04:27:48 by syamasaw          #+#    #+#             */
/*   Updated: 2024-07-18 04:27:48 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

int	export_err(char *str, int status)
{
	ft_putstr_fd(MSG_PREFIX, 2);
	ft_putstr_fd("export: ", 2);
	if (status == 1)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (status == 2)
	{
		ft_putchar_fd(str[0], 2);
		ft_putchar_fd(str[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
	return (status);
}
