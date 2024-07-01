/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bridge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:24:11 by saraki            #+#    #+#             */
/*   Updated: 2024/07/01 05:46:49 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "common.h"
#include "env.h"
#include "dbllst.h"

static void	*ret_token_str(void *data);

int	exec_tokenslst_cmds(t_blst *tokens_lst, t_blst *env_lst, int *status)
{
	void	*converted_lst;
	char	**env;

	env = convert_envlst_to_arr(env_lst);
	if (env == NULL)
		return (ERR);
	converted_lst = doub_lstdup((void *)tokens_lst, ret_token_str, NULL);
	if (converted_lst == NULL)
	{
		free_environment_array(env);
		return (ERR);
	}
	*status = exec((void *)converted_lst, env);
	doub_lstdelall((void **) &converted_lst, NULL);
	free_environment_array(env);
	return (OK);
}

// this function does not allocate memory for the new token.
static void	*ret_token_str(void *node_data)
{
	t_token_data	*token_data;

	token_data = (t_token_data *)node_data;
	return ((void *)token_data->token_str);
}
