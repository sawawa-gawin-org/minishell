/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_int.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:23:14 by saraki            #+#    #+#             */
/*   Updated: 2024/05/15 07:19:16 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INT_H
# define EXEC_INT_H

# include "dbllst.h"
# include "libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>

# include <sys/wait.h> // Linux
# include <sys/stat.h> // Linux

# define OK 0
# define ERR -1

extern char		**environ;

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		pipe_in_fd;
	int		pipe_out_fd;
	int		file_in_fd;
	int		file_out_fd;
	pid_t	pids;
	void	*head_node;
	int		index;
}				t_pipex;

typedef struct s_node
{
	struct s_node	*prev;
	union
	{
		t_pipex		*pipe_data;
		char		*str;
	}	u_data;
	struct s_node	*next;
}				t_blst;

typedef t_blst	t_tokenlst;
typedef t_blst	t_pipelst;
typedef void	(*t_callback)(char **, char *, t_pipex *);

int				make_processes(
					t_tokenlst *token_head_node,
					t_pipelst *pipe_head_node);
int				make_process(
					t_tokenlst *token_head_node,
					t_pipelst *pipe_head_node,
					t_callback callback);

char			*find_cmd(char *path);

void			do_first_process(char **cmd, char *path, t_pipex *pipe);
void			do_middle_process(char **cmd, char *path, t_pipex *pipe);
void			do_last_process(char **cmd, char *path, t_pipex *pipe);

#endif
