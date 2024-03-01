/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:29:17 by saraki            #+#    #+#             */
/*   Updated: 2023/09/25 17:48:52 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dst_len = 0;
	src_len = ft_strlen(src);
	if (dst != NULL)
		dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	i = 0;
	j = dst_len;
	while (i < size - dst_len - 1 && src[i] != '\0')
	{
		dst[j] = src[i];
		i ++;
		j ++;
	}
	dst[j] = '\0';
	return (dst_len + src_len);
}

// strlcat(dest, NULL, 0); Err
// strlcat(NULL, src, 0); Pass : return strlen(src)
// strlcat(NULL, NULL, 0); Err
// #include <stdio.h>
// #include <string.h> 
// int main(void)
// {
// 	size_t	i = 0, j = 0;
//     char dest1[30] = "5aac1a4-39f2";
// 	char dest2[30] = "5aac1a4-39f2";

// 	i = strlcat(dest1, ",Alice", 10);
// 	j = ft_strlcat(dest2, ",Alice", 10);
// 	printf("%s\t", dest1);
// 	printf("%s\n", dest2);
// 	printf("%d\n", (int) j);

// 	i = strlcat(dest1, ",Alice", 18);
// 	j = ft_strlcat(dest2, ",Alice", 18);
// 	printf("%s\t", dest1);
// 	printf("%s\n", dest2);	
// 	printf("%d\n", (int) j);

// 	i = strlcat(dest1, ",Bobby", 22);
// 	j = ft_strlcat(dest2, ",Bobby", 22);
// 	printf("%s\t", dest1);
// 	printf("%s\n", dest2);
// 	printf("%d\n", (int) j);
// 	/* NULL test */
// 	i = strlcat(NULL, dest1, 0);
// 	j = ft_strlcat(NULL, dest1, 0);
// 	printf("%d\t%d\n", (int) i, (int) j);
// }
