/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:08:56 by saraki            #+#    #+#             */
/*   Updated: 2024/06/26 14:11:52 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	malloc_error(void)
{
	char	*prefix;
	char	*middle;

	prefix = MSG_PREFIX;
	middle = "malloc";
	if (write(STDERR_FILENO, prefix, ft_strlen(prefix)) == -1)
		perror("write");
	if (write(STDERR_FILENO, middle, ft_strlen(middle)) == -1)
		perror("write");
	perror(NULL);
	return (ERR);
}
