/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:00:28 by syamasaw          #+#    #+#             */
/*   Updated: 2024/09/15 19:11:51 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static int	redirection(t_tokenlst *now_node, t_pipex *pipe);
static int	open_in_files(char *dist, t_pipex *pipex, int heredocflag);
static int	open_out_files(char *dist, t_pipex *pipex, int appendflag);
static int	open_and_send_string_to_fd(char *str);

// # Description
// This function merges the redirection tokens into one token.
// remove ">", ">>", "<", "<<"
int	parse_redirects(t_tokenlst *now_node, t_pipex *pipe)
{
	t_token_data	*token_data;
	t_tokens		type;

	token_data = now_node->u_data.token_data;
	while (now_node->u_data.token_data != NULL
		&& token_data->token_type != TUBE_FLAG)
	{
		token_data = now_node->u_data.token_data;
		type = token_data->token_type;
		if (type & (LESS_FLAG | GREAT_FLAG | HEREDOC_FLAG | APPEND_FLAG))
		{
			if (redirection(now_node, pipe))
				return (ERR);
		}
		now_node = now_node->next;
	}
	return (OK);
}

static int	redirection(t_tokenlst *now_node, t_pipex *pipe)
{
	t_tokens		symbol;
	t_token_data	*dist;
	int				err;

	symbol = now_node->u_data.token_data->token_type;
	dist = now_node->next->u_data.token_data;
	err = OK;
	if (symbol == GREAT_FLAG && dist->token_type != AMBIGUOUS_REDIRECTION_FLAG)
		err = open_out_files(dist->token_str, pipe, 0);
	else if (symbol == APPEND_FLAG && dist->token_type != AMBIGUOUS_REDIRECTION_FLAG)
		err = open_out_files(dist->token_str, pipe, 1);
	else if (symbol == LESS_FLAG && dist->token_type != AMBIGUOUS_REDIRECTION_FLAG)
		err = open_in_files(dist->token_str, pipe, 0);
	else if (symbol == HEREDOC_FLAG && dist->token_type != AMBIGUOUS_REDIRECTION_FLAG)
		err = open_in_files(dist->token_str, pipe, 1);
	else if (dist->token_type == AMBIGUOUS_REDIRECTION_FLAG)
		err = ambiguous_redir_err(dist->token_str);
	return (err);
}

static int	open_in_files(char *dist, t_pipex *pipex, int heredocflag)
{
	int	fd;

	if (dist && heredocflag == 0)
		pipex->file_in_fd = open_file_for_read(dist);
	else if (dist && heredocflag)
	{
		fd = open_and_send_string_to_fd(dist);
		pipex->file_in_fd = fd;
	}
	if (pipex->file_in_fd == -1)
	{
		close(pipex->file_out_fd);
		return (ERR);
	}
	return (OK);
}

static int	open_out_files(char *dist, t_pipex *pipex, int appendflag)
{
	if (ft_strcmp(dist, "") == 0 && access(dist, F_OK) == -1)
		pipex->file_out_fd = no_such_file_or_directory_error(dist);
	else if (dist && access(dist, F_OK) == -1 && appendflag == 0)
		pipex->file_out_fd = open(
				dist, O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);
	else if (dist && access(dist, F_OK) == -1 && appendflag)
		pipex->file_out_fd = open(
				dist, O_CREAT | O_WRONLY | O_APPEND, S_IREAD | S_IWRITE);
	else if (dist && access(dist, F_OK) == 0)
		pipex->file_out_fd = open_existing_file_for_write(dist, appendflag);
	if (pipex->file_out_fd == -1)
	{
		close(pipex->file_in_fd);
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
