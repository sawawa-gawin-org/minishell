/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:56:23 by saraki            #+#    #+#             */
/*   Updated: 2023/09/27 17:33:57 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s ++)
		len ++;
	return (len);
}

// #include <string.h>
// #include <stdio.h>
// int main(){
// 	int a = (int) ft_strlen("Hello");
// 	printf("%d\n", a);
// 	// a = (int) strlen(NULL); // Error
// }
