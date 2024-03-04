/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:36:39 by saraki            #+#    #+#             */
/*   Updated: 2023/08/22 16:04:34 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_match;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	last_match = NULL;
	while (i <= len)
	{
		if ((unsigned char) s[i] == (unsigned char) c)
			last_match = (char *)(s + i);
		i ++;
	}
	return (last_match);
}

// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	char *s = "tHello World";
// 	char *p1 = ft_strrchr(s, 'o' + 256);
// 	char *p2 = strrchr(s, 'o' + 256);
// 	printf("%p\n", p1);
// 	printf("%p\n", p2);
// }
