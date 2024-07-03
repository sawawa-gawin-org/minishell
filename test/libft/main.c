/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:42:06 by saraki            #+#    #+#             */
/*   Updated: 2024/03/01 15:01:39 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

void	print_is_NULL(char *input)
{
	if (input == NULL)
		printf("a is NULL\n");
	else
		printf("a is not NULL\n");
}

int	main()
{
    void *mem;
    mem = malloc(9223372036854775807);
    if (mem == NULL) {
        perror(NULL);
		printf("malloc failed\n");
        return (1);
    }
	printf("malloc success\n");
    free(mem);
    return (0);
	// char	*result = ft_itoa(2147483647);
	// printf("%s\n", result);
	// free(result);
	// result = NULL;

	// result = ft_itoa(-2147483648);
	// printf("%s\n", result);
	// free(result);
	// result = NULL;

	// result = ft_itoa(100);
	// printf("%s\n", result);
	// free(result);
	// result = NULL;

	// result = ft_itoa(0);
	// printf("%s\n", result);
	// free(result);
	// result = NULL;

	// result = ft_itoa(-100);
	// printf("%s\n", result);
	// free(result);
	// result = NULL;
}
