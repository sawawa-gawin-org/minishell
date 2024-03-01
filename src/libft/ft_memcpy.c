/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 05:17:58 by saraki            #+#    #+#             */
/*   Updated: 2023/09/25 17:34:44 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*u_dest;
	unsigned char	*u_src;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	u_dest = (unsigned char *) dest;
	u_src = (unsigned char *) src;
	while (i < n)
	{
		u_dest[i] = u_src[i];
		i ++;
	}
	return (dest);
}

// #include <string.h>
// #include <stdio.h>
// int main(){
// 	char dst[] = "Hello World";
// 	char src[] = "Hello Hello Hello Hello Hello Hello Hello ";
// 	char *temp = ft_memcpy(dst, src, 10);
// 	char dst2[] = "Hello World";
// 	char src2[] = "Hello Hello Hello Hello Hello Hello Hello ";
// 	char *temp2 = memcpy(dst2, src2, 10);
// 	printf("%s\n", temp);
// 	printf("%s\n", temp2);

// 	char dst3[] = "Hello World";
// 	char src3[] = "9999999999999999999999";
// 	char *temp3 = ft_memcpy(dst3, src3, 5);
// 	char dst4[] = "Hello World";
// 	char src4[] = "9999999999999999999999";
// 	char *temp4 = memcpy(dst4, src4, 5);
// 	printf("%s\n", temp3);
// 	printf("%s\n", temp4);

// 	char *dst_null = NULL;
// 	char *src3_null = NULL;
// 	char *temp3_null = ft_memcpy(dst_null, src3_null, 10);
// 	char *dst4_null = NULL;
// 	char *src4_null = NULL;
// 	char *temp4_null = memcpy(dst4_null, src4_null, 10);
// 	printf("%s\n", temp3_null);
// 	printf("%s\n", temp4_null);
// }
