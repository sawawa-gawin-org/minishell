/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:45:21 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/05 04:19:13 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	u_c1;
	unsigned char	u_c2;

	i = 0;
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
