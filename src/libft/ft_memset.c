/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:29 by saraki            #+#    #+#             */
/*   Updated: 2023/08/05 05:10:08 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	src;

	i = 0;
	dst = (unsigned char *) s;
	src = (unsigned char) c;
	while (i < n)
	{
		dst[i] = src;
		i ++;
	}
	return (s);
}

// #include <stdio.h>
// int main(){
// 	char str[] = "Hello World";
// 	ft_memset(str, 32, 10);
// 	printf("%s\n", str);
// }
