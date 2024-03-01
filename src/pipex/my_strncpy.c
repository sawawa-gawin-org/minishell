/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:59:39 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/01 17:23:13 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*my_strncpy(char *dest, char *src, int n)
{
	char	*ret;

	ret = dest;
	while (*src && n--)
		*dest++ = *src++;
	*dest = '\0';
	return (ret);
}
