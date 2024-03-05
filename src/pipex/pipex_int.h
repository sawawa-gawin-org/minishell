/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:23:40 by saraki            #+#    #+#             */
/*   Updated: 2024/03/05 05:39:51 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* internal header file for pipex */

#ifndef PIPEX_INT_H
# define PIPEX_INT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>

# include <sys/wait.h> // Linux
# include <sys/stat.h> // Linux

typedef struct s_pipex
{
	int		io_fds[2];
	int		pipe_fds[2];
	pid_t	pids[2];
}		t_pipex;

int		close_fd(int *fds, int exit_code);
void	free_split(char **s);
void	exit_closepipe(t_pipex *pipex);

char	*find_cmd(char *path, char *envp[]);
char	*my_strncpy(char *dest, char *src, int n);
void	make_child_1(char *arg, char *envp[], t_pipex *pipex);
void	make_child_2(char *arg, char *envp[], t_pipex *pipex);

void	spawn_children(char **units, t_pipex pipex, char **envp);
char	*join_args_with_space(int argc, char **argv);

#endif