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
static int	redirection_for_leftend(t_tokenlst **now_node, t_pipex *pipe);
static void	open_io_files(char *symbol, char *dist, t_pipex *pipe);

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
	open_io_files(symbol->u_data.str, dist->u_data.str, pipe);
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
	open_io_files(symbol, dist->u_data.str, pipe);
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

static void	open_io_files(char *symbol, char *dist, t_pipex *pipe)
{
	if (ft_strcmp(symbol, ">") == 0)
		open_out_files(dist, pipe, 0);
	else if (ft_strcmp(symbol, ">>") == 0)
		open_out_files(dist, pipe, 1);
	else if (ft_strcmp(symbol, "<") == 0)
		open_in_files(dist, pipe, 0);
	else if (ft_strcmp(symbol, "<<") == 0)
		open_in_files(dist, pipe, 1);
}
