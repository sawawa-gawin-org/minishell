/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_int.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:23:14 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 18:38:00 by saraki           ###   ########.fr       */
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
	t_blst		**env_lst;
	char		**env;
	int			status;
	int			is_exit_called;
}				t_exec_parametors;

typedef struct s_callback_parametors
{
	char		**cmd;
	char		*path;
	t_pipex		*pipe;
	t_blst		**env_lst;
	char		**env;
	int			status;
}				t_callback_parametors;

typedef void	(*t_callback)(t_callback_parametors *);

int				exec(
					t_tokenlst **token_head_node,
					char **env,
					t_blst **env_lst);
t_tokenlst		*shift_token_section(t_tokenlst *token_head_node, int index);

int				make_processes(t_exec_parametors *param);
int				make_process(t_exec_parametors *param, t_callback callback);

char			**parse_cmd(t_tokenlst **head_node, t_pipex *pipe);

char			**convert_tokenlst_to_char_array(
					t_tokenlst *section_start_node);
char			*find_cmd(char *path, char **env, int *status);
void			parse_redirects(t_tokenlst **now_node, t_pipex *pipe);
void			do_first_process(t_callback_parametors *params);
void			do_middle_process(t_callback_parametors *params);
void			do_last_process(t_callback_parametors *params);

#endif
