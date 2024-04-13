/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:30:28 by saraki            #+#    #+#             */
/*   Updated: 2024/04/10 12:16:50 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "dbllst.h"
# include "libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>

# include <sys/wait.h> // Linux
# include <sys/stat.h> // Linux

int	exec(void *token_head_node);

#endif