/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 07:07:07 by saraki            #+#    #+#             */
/*   Updated: 2023/09/27 17:42:25 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *) big);
	if (len == 0)
		return (0);
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	if (len < little_len)
		return (NULL);
	i = 0;
	while (i < len - little_len + 1 && big[i] != '\0')
	{
		if (big[i] == little[0] && !ft_strncmp(big + i, little, little_len))
			return ((char *) big + i);
		i ++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h> 
// int main(void)
// {
//     char str[] = "5aac1a4";
//     char to_find1[] = "aac";
// 	printf("initial:%p\n", str);
// 	printf("%p\t", strnstr(str, to_find1, 4));
// 	printf("%p\n", ft_strnstr(str, to_find1, 4));
// 	printf("%p\t", strnstr(str, to_find1, 2));
// 	printf("%p\n", ft_strnstr(str, to_find1, 2));
// 	printf("%p\t", strnstr(str, to_find1, 10));
// 	printf("%p\n", ft_strnstr(str, to_find1, 10));
// 	char to_find2[] = "#";
// 	printf("%p\t", strnstr(str, to_find2, 4));
// 	printf("%p\n", ft_strnstr(str, to_find2, 4));
// 	char to_find3[] = "\0";
// 	printf("%p\t", strnstr(str, to_find3, 4));
// 	printf("%p\n", ft_strnstr(str, to_find3, 4));
// 	printf("%p\t", strnstr(NULL, to_find1, 0));
// 	printf("%p\n", ft_strnstr(NULL, to_find1, 0));
// 	//not error
// 	printf("%p\t", strnstr(NULL, "to_find1", 0));
// 	printf("%p\n", ft_strnstr(NULL, "to_find1", 0));
// 	//error
// 	// printf("%p\t", strnstr(NULL, "to_find1", 1));
// 	// printf("%p\n", ft_strnstr(NULL, "to_find1", 1));
// }

// strnstr(str, NULL, 0) Pass
// strnstr(str, NULL, 4) Err
// strnstr(NULL, NULL, 0) Err
// strnstr(NULL, NULL, 4) Err