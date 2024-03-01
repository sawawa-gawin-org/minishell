/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:23:33 by saraki            #+#    #+#             */
/*   Updated: 2023/09/24 09:44:51 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	u_c1;
	unsigned char	u_c2;

	i = 0;
	while (i < n && !(s1[i] == '\0' && s2[i] == '\0'))
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
// int main(void)
// {
// 	printf(
// 		"ture:%d\tmyAns:%d\n",
// 		strncmp("Beca", "Because", 5),
// 		ft_strncmp("Beca", "Because", 5)
// 	);
// 	printf(
// 		"ture:%d\tmyAns:%d\n",
// 		strncmp("Beca", "Because", 10),
// 		ft_strncmp("Beca", "Because", 10)
// 	);
// 	printf(
// 		"ture:%d\tmyAns:%d\n",
// 		strncmp("ft_strncmp", "ft_strcmp", 3),
// 		ft_strncmp("ft_strncmp", "ft_strcmp", 3)
// 	);
// 	printf(
// 		"ture:%d\tmyAns:%d\n",
// 		strncmp("qwerasdf", "qwerty", 3),
// 		ft_strncmp("qwerasdf", "qwerty", 3)
// 	);
// 	printf(
// 		"ture:%d\tmyAns:%d\n",
// 		strncmp("NULL", NULL, 0),
// 		ft_strncmp("NULL", NULL, 0)
// 	);	
// 	printf(
// 		"ture:%d\tmyAns:%d\n",
// 		strncmp(NULL, "NULL", 0),
// 		ft_strncmp(NULL, "NULL", 0)
// 	);	
// 	printf(
// 		"ture:%d\tmyAns:%d\n",
// 		strncmp(NULL, NULL, 0),
// 		ft_strncmp(NULL, NULL, 0)
// 	);

// 	char *sample = (char *)calloc(10, 1);
// 	strlcpy(sample, "libft", 10);
// 	sample[5] = -42;
// 	printf(
// 		"ture:%d\tmyAns:%d\n",
// 		strncmp("libft", sample, 6),
// 		ft_strncmp("libft", sample, 6)
// 	);
// 	free(sample);	
// }
