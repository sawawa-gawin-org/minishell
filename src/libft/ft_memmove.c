/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 05:33:07 by saraki            #+#    #+#             */
/*   Updated: 2023/09/25 17:31:06 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*u_dest;
	unsigned char	*u_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	u_dest = (unsigned char *) dest;
	u_src = (unsigned char *) src;
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else
	{
		i = n;
		while (i > 0)
		{
			u_dest[i - 1] = u_src[i - 1];
			i --;
		}
		return (dest);
	}
}

// #include <string.h>
// #include <stdio.h>
// int main(){
// 	char dst1[] = "Hello, World!";
// 	char dst2[] = "Hello, World!";
// 	char *temp1;
// 	char *temp2;
// 	temp1 = memmove(dst1 + 4, dst1, 9);
// 	printf("%s\n", dst1);
// 	printf("%s\n", temp1);
// 	temp2 = ft_memmove(dst2 + 4, dst2, 9);
// 	printf("%s\n", dst2);
// 	printf("%s\n", temp2);
// 	char dst3[] = "Hello, World!";
// 	char dst4[] = "Hello, World!";
// 	char *temp3;
// 	char *temp4;
// 	temp3 = memmove(dst3, dst3 + 4, 9);
// 	printf("%s\n", dst3);
// 	printf("%s\n", temp3);
// 	temp4 = ft_memmove(dst4, dst4 + 4, 9);
// 	printf("%s\n", dst4);
// 	printf("%s\n", temp4);
// }
