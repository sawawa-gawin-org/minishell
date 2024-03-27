/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:23:15 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/27 14:32:54 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "dbllst.h"

int	is_blank(int c)
{
	return (c == ' ' || c == '\t');
}

int	is_blank_str(char *str)
{
	int	i;

	i = 0;
	while (is_blank(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
