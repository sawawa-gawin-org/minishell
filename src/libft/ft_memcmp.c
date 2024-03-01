/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 06:39:46 by saraki            #+#    #+#             */
/*   Updated: 2023/08/05 07:09:33 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*string1;
	unsigned char	*string2;

	string1 = (unsigned char *) s1;
	string2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (string1[i] != string2[i])
			return ((int) string1[i] - (int)string2[i]);
		i ++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h> 
// int main(void)
// {
// 	printf(
// 		"ture:%d\tmyAns:%d\n",
// 		memcmp("Beca", "Because", 5),
// 		ft_memcmp("Beca", "Because", 5)
// 	);
// 	printf(
// 		"ture:%d\tmyAns:%d\n",
// 		memcmp("Beca", "Because", 10),
// 		ft_memcmp("Beca", "Because", 10)
// 	);
// 	printf(
// 		"ture:%d\tmyAns:%d\n",
// 		memcmp("ft_strncmp", "ft_strcmp", 3),
// 		ft_memcmp("ft_strncmp", "ft_strcmp", 3)
// 	);
// }
