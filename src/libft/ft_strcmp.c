/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:10:33 by saraki            #+#    #+#             */
/*   Updated: 2024/05/07 17:18:41 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// This is the extra function that is not in the original libft.
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	u_c1;
	unsigned char	u_c2;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (0);
	while (!(s1[i] == '\0' && s2[i] == '\0'))
	{
		u_c1 = (unsigned char) s1[i];
		u_c2 = (unsigned char) s2[i];
		if (u_c1 != u_c2)
			return ((int)(u_c1 - u_c2));
		i ++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	printf("original: %d\n", strcmp("ABCDEFG", "ABCDEFG"));
// 	printf("ft: %d\n", ft_strcmp("ABCDEFG", "ABCDEFG"));
// 	printf("--------------------\n");
// 	printf("original: %d\n", strcmp("NULL", "ABCDEFG")); // ret > 0
// 	printf("ft: %d\n", ft_strcmp("NULL", "ABCDEFG")); // ret > 0
// 	printf("--------------------\n");
// 	printf("original: %d\n", strcmp("0ULL", "ABCDEFG")); // ret < -1
// 	printf("ft: %d\n", ft_strcmp("0ULL", "ABCDEFG")); // ret < -1
// 	printf("--------------------\n");
// 	printf("original: %d\n", strcmp(NULL, NULL)); // ret 0
// 	printf("ft: %d\n", ft_strcmp(NULL, NULL)); // ret 0
// 	printf("--------------------\n");
// 	printf("original: %d\n", strcmp(NULL, "ABCDEFG")); // ret segfault
// 	printf("ft: %d\n", ft_strcmp(NULL, "ABCDEFG"));  // ret segfault
// }