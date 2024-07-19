/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_processes_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:25:30 by saraki            #+#    #+#             */
/*   Updated: 2024/07/01 08:59:59 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static int	make_process_builtin(t_exec_parametors *param, t_callback callback,
				t_callback_parametors *callback_args);
static int	make_process_nonbuiltin(t_callback_parametors *callback_args,
				t_callback callback);

int	make_process(t_exec_parametors *param, t_callback callback)
{
	t_callback_parametors	callback_args;
	t_tokenlst				*start_node;

	callback_args.pipe = param->pipe_list->u_data.pipe_data;
	callback_args.status = 0;
	start_node = shift_token_section(param->token_list,
			callback_args.pipe->index);
	callback_args.cmd = parse_cmd(start_node, callback_args.pipe);
	if (callback_args.cmd == NULL)
		return (ERR_ALLOCATE_MEMORY);
	if (is_builtin(callback_args.cmd[0]))
		return (make_process_builtin(param, callback, &callback_args));
	callback_args.path = find_cmd(callback_args.cmd[0], param->env,
			&(callback_args.status));
	if (!callback_args.path && callback_args.status == CMD_NOT_FOUND)
		cmdnotfound_error(callback_args.cmd[0]);
	else if (!callback_args.path && callback_args.status == CMD_CNT_EXECUTE)
		cmdnotexecutable_error(callback_args.cmd[0]);
	callback_args.env = param->env;
	return (make_process_nonbuiltin(&callback_args, callback));
}

static int	make_process_nonbuiltin(t_callback_parametors *callback_args,
		t_callback callback)
{
	callback_args->pipe->pids = fork();
	if (callback_args->pipe->pids == 0)
		callback(callback_args);
	free(callback_args->cmd);
	free(callback_args->path);
	if (callback_args->pipe->pids < 0)
		return (GENERAL_ERR);
	return (OK);
}

static int	make_process_builtin(t_exec_parametors *param, t_callback callback,
		t_callback_parametors *callback_args)
{
	callback_args->status = 0;
	callback_args->env_lst = param->env_lst;
	callback_args->pipe->pids = fork();
	if (callback_args->pipe->pids == 0)
		callback(callback_args);
	free(callback_args->cmd);
	if (callback_args->pipe->pids < 0)
		return (GENERAL_ERR);
	return (OK);
}

t_tokenlst	*shift_token_section(t_tokenlst *token_head_node, int index)
{
	int			i;
	t_tokenlst	*node;

	i = 0;
	node = token_head_node;
	while (i < index && node->u_data.str != NULL)
	{
		node = node->next;
		if (ft_strcmp(node->u_data.str, "|") == 0)
		{
			i++;
			node = node->next;
		}
	}
	return (node);
}
