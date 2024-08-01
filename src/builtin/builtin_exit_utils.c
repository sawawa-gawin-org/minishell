/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:14:12 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 17:06:09 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"

static size_t	parse_ssize_from_zero_to_max(const char *nptr, char **endptr);
static int		strip_sign(char **endptr);

int	parse_str_to_numeric(char *argv, size_t *value)
{
	char	*endptr;
	int		flag;

	flag = 0;
	*value = parse_ssize_from_zero_to_max(argv, &endptr);
	if (*endptr != '\0')
		flag = 1;
	return (flag);
}

static size_t	parse_ssize_from_zero_to_max(const char *nptr, char **endptr)
{
	long			sum;
	int				sign;
	int				delta;

	if (nptr == NULL || endptr == NULL)
		return (0);
	*endptr = (char *) nptr;
	sign = strip_sign(endptr);
	sum = 0;
	while (**endptr >= '0' && **endptr <= '9')
	{
		if (sum > (long) SSIZE_MAX / 10)
			return (SSIZE_MAX);
		sum *= 10;
		delta = (int) **endptr - (int) '0';
		if (sum > SSIZE_MAX - (long) delta)
			return (SSIZE_MAX);
		sum += delta;
		(*endptr) += 1;
	}
	return (sign * sum);
}

static int	strip_sign(char **endptr)
{
	int	sign;

	if (endptr == NULL || *endptr == NULL)
		return (0);
	sign = 1;
	if (**endptr == '+' || **endptr == '-')
	{
		if (**endptr == '-')
			sign *= -1;
		(*endptr) += 1;
	}
	return (sign);
}
