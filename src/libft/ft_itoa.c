/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 07:31:57 by saraki            #+#    #+#             */
/*   Updated: 2023/08/07 08:19:20 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	int_to_str(char *result, unsigned int value, int location);
static int	count_digit(unsigned int value);

char	*ft_itoa(int n)
{
	unsigned int	value;
	int				digits;
	char			*result;

	digits = 0;
	if (n < 0)
	{
		value = -1 * n;
		digits += 1;
	}
	else
		value = n;
	digits += count_digit(value);
	result = (char *) ft_calloc(sizeof(char), digits + 1);
	if (result == NULL)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	int_to_str(result, value, digits);
	return (result);
}

static void	int_to_str(char *result, unsigned int value, int location)
{
	unsigned int	residual;

	if (value < 10)
	{
		result[location - 1] = (char)(value + (int) '0');
		return ;
	}
	else
	{
		residual = value % 10;
		int_to_str(result, value / 10, location - 1);
		result[location - 1] = (char)(residual + (int) '0');
	}
}

static int	count_digit(unsigned int value)
{
	int	digits;
	int	power;

	power = 1;
	digits = 1;
	while (value / power > 9)
	{
		power *= 10;
		digits ++;
	}
	return (digits);
}

// #include <stdio.h>
// int	main()
// {
// 	char	*result = ft_itoa(2147483647);
// 	printf("%s\n", result);
// 	free(result);
// 	result = NULL;

// 	result = ft_itoa(-2147483648);
// 	printf("%s\n", result);
// 	free(result);
// 	result = NULL;

// 	result = ft_itoa(100);
// 	printf("%s\n", result);
// 	free(result);
// 	result = NULL;

// 	result = ft_itoa(0);
// 	printf("%s\n", result);
// 	free(result);
// 	result = NULL;

// 	result = ft_itoa(-100);
// 	printf("%s\n", result);
// 	free(result);
// 	result = NULL;
// }
