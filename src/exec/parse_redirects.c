/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:00:28 by syamasaw          #+#    #+#             */
/*   Updated: 2024/06/30 00:56:32 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static int	redirection(t_tokenlst **now_node, t_pipex *pipe);
static int	open_in_files(char *dist, t_pipex *pipex, int heredocflag);
static int	open_out_files(char *dist, t_pipex *pipex, int appendflag);
static int	open_and_send_string_to_fd(char *str);

static int	redirection_for_leftend(t_tokenlst **now_node, t_pipex *pipe);

// # Description
// This function merges the redirection tokens into one token.
// remove ">", ">>", "<", "<<"
void	parse_redirects(t_tokenlst **now_node, t_pipex *pipe)
{
	char		*token;
	t_tokenlst	*init_node;

	init_node = *now_node;
	token = (*now_node)->u_data.str;
	while ((*now_node)->u_data.str != NULL && ft_strcmp(token, "|") != 0)
	{
		token = (*now_node)->u_data.str;
		if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
			|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
		{
			if ((*now_node)->prev->u_data.token_data == NULL)
			{
				if (redirection_for_leftend(now_node, pipe))
					break ;
				token = (*now_node)->u_data.str;
			}
			else if (redirection(now_node, pipe))
				break ;
			continue ;
		}
		(*now_node) = (*now_node)->next;
	}
	*now_node = init_node;
	return ;
}

static int	redirection(t_tokenlst **now_node, t_pipex *pipe)
{
	t_tokenlst	*symbol;
	t_tokenlst	*dist;

	symbol = (t_tokenlst *)doub_lstpurge((void **)now_node);
	dist = (t_tokenlst *)doub_lstpurge((void **)now_node);
	if (ft_strcmp(symbol->u_data.str, ">") == 0)
		open_out_files(dist->u_data.str, pipe, 0);
	else if (ft_strcmp(symbol->u_data.str, ">>") == 0)
		open_out_files(dist->u_data.str, pipe, 1);
	else if (ft_strcmp(symbol->u_data.str, "<") == 0)
		open_in_files(dist->u_data.str, pipe, 0);
	else if (ft_strcmp(symbol->u_data.str, "<<") == 0)
		open_in_files(dist->u_data.str, pipe, 1);
	doub_lstdelone((void *)symbol, NULL);
	doub_lstdelone((void *)dist, NULL);
	return (OK);
}

// リダイレクトが一番左の場合だけ、先頭をパージせずに、先頭以外をパージして情報部分を先頭へ移動させる
// < infile echo a
// <をechoに変える、infileとechoをパージ
// < infile |
// <を|に変える、infileと|をパージ
// < infile の場合、<をNULLに変える
static int	redirection_for_leftend(t_tokenlst **now_node, t_pipex *pipe)
{
	char		*symbol;
	t_tokenlst	*dist;

	symbol = (*now_node)->u_data.str;
	(*now_node) = (*now_node)->next;
	dist = (t_tokenlst *)doub_lstpurge((void **)now_node);
	(*now_node) = (*now_node)->prev;
	if (ft_strcmp(symbol, ">") == 0)
		open_out_files(dist->u_data.str, pipe, 0);
	else if (ft_strcmp(symbol, ">>") == 0)
		open_out_files(dist->u_data.str, pipe, 1);
	else if (ft_strcmp(symbol, "<") == 0)
		open_in_files(dist->u_data.str, pipe, 0);
	else if (ft_strcmp(symbol, "<<") == 0)
		open_in_files(dist->u_data.str, pipe, 1);
	doub_lstdelone((void *)dist, NULL);
	if ((*now_node)->next != NULL)
	{
		(*now_node)->u_data.str = (*now_node)->next->u_data.str;
		(*now_node)->u_data.env_data = (*now_node)->next->u_data.env_data;
		(*now_node)->u_data.token_data = (*now_node)->next->u_data.token_data;
		(*now_node)->u_data.pipe_data = (*now_node)->next->u_data.pipe_data;
		(*now_node) = (*now_node)->next;
		doub_lstdelone(doub_lstpurge((void **)now_node), NULL);
	}
	else
		(*now_node)->u_data.str = NULL;
	return (OK);
}

static int	open_in_files(char *dist, t_pipex *pipex, int heredocflag)
{
	int	fd;

	if (dist && access(dist, R_OK) == 0 && heredocflag == 0)
		pipex->file_in_fd = open(dist, O_RDONLY);
	else if (dist && heredocflag)
	{
		fd = open_and_send_string_to_fd(dist);
		pipex->file_in_fd = fd;
	}
	if (pipex->file_in_fd == -1)
	{
		close(pipex->file_in_fd);
		close(pipex->file_out_fd);
		return (ERR);
	}
	return (OK);
}

static int	open_out_files(char *dist, t_pipex *pipex, int appendflag)
{
	if (dist && access(dist, F_OK) == -1 && appendflag == 0)
		pipex->file_out_fd = open(
				dist, O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);
	else if (dist && access(dist, F_OK) == 0 && appendflag == 0)
		pipex->file_out_fd = open(dist, O_WRONLY);
	else if (dist && access(dist, F_OK) == -1 && appendflag)
		pipex->file_out_fd = open(
				dist, O_CREAT | O_WRONLY | O_APPEND, S_IREAD | S_IWRITE);
	else if (dist && access(dist, F_OK) == 0 && appendflag)
		pipex->file_out_fd = open(dist, O_WRONLY | O_APPEND);
	if (pipex->file_out_fd == -1)
	{
		close(pipex->file_in_fd);
		close(pipex->file_out_fd);
		return (ERR);
	}
	return (OK);
}

static int	open_and_send_string_to_fd(char *str)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (ERR);
	if (write(fd[1], str, ft_strlen(str)) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (ERR);
	}
	close(fd[1]);
	return (fd[0]);
}
