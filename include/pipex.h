/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:42:11 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/09 10:19:26 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>

# include <sys/wait.h> // Linux
# include <sys/stat.h> // Linux

# define OK 0
# define ERR -1

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

int		close_fds(t_pipex *pipe_arr, int size, int exit_code);
int		free_split(char **s, int exit_code);
int		count_units(char **units);
int		pipe_fds(int *in_fd, int *out_fd);

char	*find_cmd(char *path, char *envp[]);
void	make_child_1(char *arg, char *envp[], t_pipex *pipex);
void	make_child_2(char *arg, char *envp[], t_pipex *pipex);

int		spawn_children(char **units, int size, t_pipex *pipex_arr, char **envp);
int		make_oldest_child(char *phrase, t_pipex *pipe, char *envp[]);
int		make_middle_child(char *phrase, t_pipex *pipe, char *envp[]);
int		make_youngest_child(char *phrase, t_pipex *pipe, char *envp[]);

int		pipex(int argc, char *argv[], char *envp[]);

#endif