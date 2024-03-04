/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 05:13:16 by saraki            #+#    #+#             */
/*   Updated: 2023/08/23 04:03:07 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*dst;

	i = 0;
	dst = (unsigned char *) s;
	while (i < n)
	{
		dst[i] = '\0';
		i ++;
	}
	return ;
}

// #include <stdio.h>
// int main(){
// 	char str[] = "Hello World";
// 	ft_bzero(str, 10);
// 	printf("%s\n", str);
// }
