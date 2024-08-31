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
	char *a;

	a = ft_strjoin_with_sep("key", "value", '=');
	printf("%s\n", a);
	free(a);
	
	a = ft_strjoin_with_sep("key", NULL, '=');
	printf("%s\n", a);
	free(a);

	a = ft_strjoin_with_sep(NULL, "value", '=');
	printf("%s\n", a);
	free(a);

	a = ft_strjoin_with_sep(NULL, NULL, '=');
	if (a == NULL)
		printf("NULL\n");
	else
		printf("%s\n", a);
	free(a);
    return (0);
}
