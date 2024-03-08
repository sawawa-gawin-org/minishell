/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:23:40 by saraki            #+#    #+#             */
/*   Updated: 2024/03/08 09:09:33 by saraki           ###   ########.fr       */
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
	int		in_fd;
	int		out_fd;
	int		pipe_in_fd;
	int		pipe_out_fd;
	pid_t	pids;
	void	*head;
	int		index;
}		t_pipex;

char	**parse_argv(int argc, char **argv);

int		close_fd(int *fds, int exit_code);
void	free_split(char **s);
int		count_units(char **units);
int		pipe_fds(int *in_fd, int *out_fd);

char	*find_cmd(char *path, char *envp[]);
void	make_child_1(char *arg, char *envp[], t_pipex *pipex);
void	make_child_2(char *arg, char *envp[], t_pipex *pipex);

int		spawn_children(char **units, int size, t_pipex *pipex_arr, char **envp);
int		make_oldest_child(char *phrase, t_pipex *pipe, char *envp[]);
int		make_middle_child(char *phrase, t_pipex *pipe, char *envp[]);
int		make_youngest_child(char *phrase, t_pipex *pipe, char *envp[]);

#endif