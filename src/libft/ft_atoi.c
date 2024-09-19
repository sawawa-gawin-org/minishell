/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:48:47 by saraki            #+#    #+#             */
/*   Updated: 2023/09/24 16:39:15 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strip_sign(const char *str, int *sign);
static int	strip_spaces(const char *str);

int	ft_atoi(const char *nptr)
{
	int				sign;
	unsigned long	sum;
	unsigned long	pre_sum;
	int				index;

	sign = 1;
	index = strip_spaces(nptr);
	index += strip_sign(nptr + index, &sign);
	sum = 0;
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		pre_sum = sum;
		sum *= 10;
		sum += (int) nptr[index] - (int) '0';
		if (sum < pre_sum || sum > (unsigned long) LONG_MAX)
		{
			if (sign > 0)
				return ((int) LONG_MAX);
			if (sign < 0)
				return ((int) LONG_MIN);
		}
		index ++;
	}
	return (sign * (int) sum);
}

static int	strip_spaces(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i ++;
	return (i);
}

static int	strip_sign(const char *str, int *sign)
{
	int	i;

	*sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign *= -1;
		i ++;
	}
	return (i);
}
