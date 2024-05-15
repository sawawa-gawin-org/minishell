/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:00:28 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/15 08:53:21 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static int	redirection(t_tokenlst **now_node, t_pipex *pipe);
static int	open_in_files(char *dist, t_pipex *pipex);
static int	open_out_files(char *dist, t_pipex *pipex);

// # Description
// This function merges the redirection tokens into one token.
// remove ">", ">>", "<", "<<" 
int	parse_redirects(t_tokenlst **now_node, t_pipex *pipe)
{
	char		*token;
	t_tokenlst	*init_node;
	int			err;

	init_node = *now_node;
	token = (*now_node)->u_data.str;
	err = 0;
	while (token != NULL && ft_strcmp(token, "|") != 0)
	{
		if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
			|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
			err = redirection(now_node, pipe);
		if (err != 0)
			break;
		(*now_node) = (*now_node)->next;
		token = (*now_node)->u_data.str;
	}
	*now_node = init_node;
	return (err);
}

static int	redirection(t_tokenlst **now_node, t_pipex *pipe)
{
	t_tokenlst	*symbol;
	t_tokenlst	*dist;

	symbol = (t_tokenlst *)doub_lstpurge((void **)now_node);
	dist = (t_tokenlst *)doub_lstpurge((void **)now_node);
	if (ft_strcmp(symbol->u_data.str, ">") == 0)
		write(1, ">", 1);
	else if (ft_strcmp(symbol->u_data.str, ">>") == 0)
		write(1, ">>", 1);
	else if (ft_strcmp(symbol->u_data.str, "<") == 0)
		write(1, "<", 1);
	else if (ft_strcmp(symbol->u_data.str, "<<") == 0)
		write(1, "<<", 1);
	doub_lstdelone((void *)symbol, NULL);
	doub_lstdelone((void *)dist, NULL);
	return (OK);
}

static int	open_in_files(char *dist, t_pipex *pipex)
{
	if (dist && access(dist, R_OK) == 0)
		pipex->file_in_fd = open(dist, O_RDONLY);
	if (pipex->file_in_fd == -1)
	{
		close(pipex->file_in_fd);
		close(pipex->file_out_fd);
		return (ERR);
	}
	return (OK);
}

static int	open_out_files(char *dist, t_pipex *pipex)
{
	if (dist && access(dist, F_OK) == -1)
		pipex->file_out_fd = open(dist, O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);
	else if (dist && access(dist, F_OK) == 0)
		pipex->file_out_fd = open(dist, O_WRONLY);
	if (pipex->file_in_fd == -1)
	{
		close(pipex->file_in_fd);
		close(pipex->file_out_fd);
		return (ERR);
	}
	return (OK);
}
