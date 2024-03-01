/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:40:02 by saraki            #+#    #+#             */
/*   Updated: 2023/09/27 15:49:38 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*pointer;
	size_t	checked_size;

	if (n == 0 || size == 0)
	{
		checked_size = 1;
		pointer = malloc(checked_size);
	}
	else
	{
		if (SIZE_MAX / n < size)
			return (NULL);
		checked_size = n * size;
		pointer = malloc(checked_size);
	}
	if (pointer == NULL)
		return (NULL);
	ft_bzero(pointer, checked_size);
	return (pointer);
}

// #include <stdio.h>
// #include <stdint.h>
// int main() {
//     size_t num = 4;
// 	// int *a;
// 	// a = (int *) ft_calloc(0, num);
// 	// a[0] = 32;
//     // if (a != NULL) {
//     //     free(a);
//     // }
// 	return (0);
// }
