/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_int.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:23:14 by saraki            #+#    #+#             */
/*   Updated: 2024/07/17 15:42:09 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INT_H
# define EXEC_INT_H

# include "dbllst.h"
# include "libft.h"
# include "common.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>

# include <sys/wait.h> // Linux
# include <sys/stat.h> // Linux

typedef struct s_exec_parametors
{
	t_tokenlst	*token_list;
	t_pipelst	*pipe_list;
	char		**env;
	int			status;
}				t_exec_parametors;

typedef struct s_callback_parametors
{
	char		**cmd;
	char		*path;
	t_pipex		*pipe;
	char		**env;
	int			status;
}				t_callback_parametors;

typedef void	(*t_callback)(t_callback_parametors *);

int				exec(t_tokenlst **token_head_node, char **env);

int				make_processes(t_exec_parametors *param);
int				make_process(t_exec_parametors *param, t_callback callback);

char			**parse_cmd(
					t_exec_parametors *param,
					t_tokenlst **head_node,
					t_pipex *pipe);
char			*find_cmd(char *path, char **env, int *status);
void			parse_redirects(t_tokenlst **now_node, t_pipex *pipe);
void			do_first_process(t_callback_parametors *params);
void			do_middle_process(t_callback_parametors *params);
void			do_last_process(t_callback_parametors *params);

int				cmdnotfound_error(char *cmd);

#endif
