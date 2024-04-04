/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_int.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:23:14 by saraki            #+#    #+#             */
/*   Updated: 2024/04/04 16:05:51 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INT_H
# define EXEC_INT_H

# include "dbllst.h"
# include "libft.h"

# include <stdlib.h>

# define OK 0
# define ERR -1

extern char	**environ;

typedef struct s_node
{
	struct s_node	*prev;
	void			*data;
	struct s_node	*next;
}				t_blst;

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		pipe_in_fd;
	int		pipe_out_fd;
	pid_t	pids;
	int		index;
}				t_pipex;

typedef void	(*t_callback)(char **, char *, t_pipex *);

void	close_fds_in_processes(t_blst *pipe_head_node, int index);

void	do_first_process(char **cmd, char *path, t_pipex *pipe);
void	do_middle_process(char **cmd, char *path, t_pipex *pipe);
void	do_last_process(char **cmd, char *path, t_pipex *pipe);

int				ft_strcmp(const char *s1, const char *s2);

# endif