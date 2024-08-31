/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_int.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:23:14 by saraki            #+#    #+#             */
/*   Updated: 2024/08/31 20:01:23 by saraki           ###   ########.fr       */
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

// exec.c
int				exec(
					t_tokenlst **token_head_node,
					char **env,
					t_blst **env_lst);
// process.c
int				make_each_process(
					t_exec_parametors *param, t_callback callback);

// process_utils.c
int				init_pipeline(t_blst *pipe_node);
int				wait_processes(t_pipelst *pipe_node);

// parse_cmd.c
char			**parse_cmd(t_tokenlst *token_list, t_pipex *pipe);
char			**convert_tokenlst_to_char_array(
					t_tokenlst *section_start_node);

// parse_redirects.c
int				parse_redirects(t_tokenlst *now_node, t_pipex *pipe);

// parse_redirects_util.c
int				open_existing_file_for_write(char *dist, int appendflag);
int				open_file_for_read(char *dist);

// process_callback.c
void			do_first_process(t_callback_parametors *params);
void			do_middle_process(t_callback_parametors *params);
void			do_last_process(t_callback_parametors *params);

#endif
