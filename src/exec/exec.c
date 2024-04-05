/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:22:09 by saraki            #+#    #+#             */
/*   Updated: 2024/04/05 02:46:20 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

// # about head_node
// `head_node` is a linked list that stores the command line.
// exapmle:
// head_node->data = "ls"
// head_node->next->data = "-l"
// head_node->next->next->data = "|"
// head_node->next->next->next->data = "wc"
// head_node->next->next->next->next->data = "-l"

int	exec(t_tokenlst *token_head_node)
{
	t_pipelst	*pipe_head_node;

	if (token_head_node == NULL)
		return (1);
	pipe_head_node = init_pipe_lst(token_head_node);
	if (pipe_head_node == NULL)
		return (1);
	make_processes(token_head_node, pipe_head_node);
}

static t_pipelst	*init_pipe_lst(t_tokenlst	*token_head_node)
{
	int			index;
	t_pipelst	*pipe_head_node;
	t_pipelst	*new_node;

	index = 0;
	pipe_head_node = doub_lstnew(NULL);
	while (pipe_head_node != NULL && token_head_node->data != NULL)
	{
		new_node = init_pipe_node(index);
		if (new_node == NULL)
		{
			doub_lstdelall(&pipe_head_node, free);
			return (NULL);
		}
		doub_lstappend(&pipe_head_node, new_node);
		((t_pipex *) (new_node->data))->head_node = pipe_head_node;
		while (!ft_strcmp((char *)token_head_node->data, "|"))
			token_head_node = token_head_node->next;
		token_head_node = token_head_node->next;
	}
	return (pipe_head_node);
}

static t_pipelst	*init_pipe_node(int index)
{
	t_pipelst	*node;
	t_pipex		*pipedata;

	pipedata = (t_pipex *)malloc(sizeof(t_pipex));
	if (pipedata == NULL)
		return (NULL);
	pipedata->in_fd = -1;
	pipedata->out_fd = -1;
	pipedata->pipe_in_fd = -1;
	pipedata->pipe_out_fd = -1;
	pipedata->index = index;
	pipedata->pids = 0;
	node = (t_pipelst *)doub_lstnew((void *)pipedata);
	if (node == NULL)
	{
		free(pipedata);
		return (NULL);
	}
	return (node);
}
