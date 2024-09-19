/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:30:28 by saraki            #+#    #+#             */
/*   Updated: 2024/09/19 06:31:25 by saraki           ###   ########.fr       */
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

// Linux
# include <sys/wait.h> 
# include <sys/stat.h>

int	exec(void **token_head_node, char **env, void **env_lst);
int	exec_tokenslst_cmds(void *tokens_lst, void *env_lst, int *status);

#endif