/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:22:09 by saraki            #+#    #+#             */
/*   Updated: 2024/07/21 18:48:37 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "builtin.h"

static t_pipelst	*init_pipe_lst(t_tokenlst *token_head_node);
static t_pipelst	*init_pipe_node(int index);
static void			close_fds_all(t_pipelst *pipe_head_node);

/**
 * Executes a command by parsing the token list and executing the
 * appropriate actions.
 * 
 * @param token_head_node A pointer to the head node of the token list.
 * @param env An array of strings representing the environment variables.
 * @param env_lst A pointer to the head node of the environment
 *  variable linked list.
 * @return An integer representing the exit status of the executed command.
 * @details `token_head_node` is a linked list that stores the command line.
 * @example
 * 	`ls -l | wc -l`
 * 	`token_head_node` is a linked list that stores the following data:
 * 	`[ls] -> [-l] -> [|] -> [wc] -> [-l]`
 */
int	exec(t_tokenlst **token_head_node, char **env, t_blst **env_lst)
{
	t_exec_parametors	param;
	int					status;

	param.env_lst = env_lst;
	param.token_list = *token_head_node;
	param.env = env;
	param.is_exit_called = 0;
	param.pipe_list = init_pipe_lst(param.token_list);
	if (param.pipe_list == NULL)
		return (ERR_ALLOCATE_MEMORY);
	status = make_processes(&param);
	env_lst = param.env_lst;
	close_fds_all(param.pipe_list);
	doub_lstdelall((void **)&param.pipe_list, free);
	*token_head_node = param.token_list;
	if (param.is_exit_called && status != GENERAL_ERR)
		return (EXIT_CALLED);
	return (status);
}

/**
 * Initializes a pipe list for executing commands.
 *
 * This function takes a token list as input and initializes a pipe list
 * structure for executing commands. The pipe list is used to store the
 * commands and their corresponding arguments that will be executed in
 * separate processes connected by pipes.
 * @example The following token list:
 * 	ls -l | wc -l
 * will be converted to the following pipe list:
 * 	[ls -l] -> [wc -l]
 * @param token_head_node The head node of the token list.
 * @return A pointer to the initialized pipe list.
 */
static t_pipelst	*init_pipe_lst(t_tokenlst *token_head_node)
{
	int			index;
	t_pipelst	*pipe_head_node;
	t_pipelst	*new_node;
	t_tokenlst	*token_node;

	index = 0;
	token_node = token_head_node;
	pipe_head_node = doub_lstnew(NULL);
	while (pipe_head_node != NULL && token_node->u_data.str != NULL)
	{
		new_node = init_pipe_node(index ++);
		if (new_node == NULL)
		{
			doub_lstdelall((void **)&pipe_head_node, free);
			return (NULL);
		}
		doub_lstappend((void **)&pipe_head_node, new_node);
		new_node->u_data.pipe_data->head_node = pipe_head_node;
		while (token_node->u_data.str != NULL
			&& ft_strcmp((char *)token_node->u_data.str, "|"))
			token_node = token_node->next;
		if (token_node->u_data.str != NULL)
			token_node = token_node->next;
	}
	return (pipe_head_node);
}

/**
 * Initializes a new pipe node for the given index.
 *
 * @param index The index of the pipe node.
 * @return A pointer to the newly initialized pipe node.
 */
static t_pipelst	*init_pipe_node(int index)
{
	t_pipelst	*node;
	t_pipex		*pipedata;

	pipedata = (t_pipex *)malloc(sizeof(t_pipex));
	if (pipedata == NULL)
		return (NULL);
	pipedata->pipe_in_fd = -1;
	pipedata->pipe_out_fd = -1;
	pipedata->file_in_fd = -1;
	pipedata->file_out_fd = -1;
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

static void	close_fds_all(t_pipelst *pipe_head_node)
{
	t_pipex		*pipe;
	t_pipelst	*now_node;

	now_node = pipe_head_node;
	while (now_node->u_data.pipe_data != NULL)
	{
		pipe = (t_pipex *)now_node->u_data.pipe_data;
		if (pipe->file_in_fd >= 0)
			close(pipe->file_in_fd);
		if (pipe->file_out_fd >= 0)
			close(pipe->file_out_fd);
		if (pipe->pipe_in_fd >= 0)
			close(pipe->pipe_in_fd);
		if (pipe->pipe_out_fd >= 0)
			close(pipe->pipe_out_fd);
		now_node = now_node->next;
	}
}
