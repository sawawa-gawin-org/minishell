/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bridge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:24:11 by saraki            #+#    #+#             */
/*   Updated: 2024/06/26 02:08:23 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"
#include "exec.h"
#include "env.h"

static void	*ret_token_str(void *data);

int	exec_tokenslst_cmds(t_blst *tokens_lst, t_blst *env_lst, int *status)
{
	void	*converted_lst;
	char	**env;
	int		err;

	err = 0;
	env = convert_envlst_to_arr(env_lst);
	if (env == NULL)
		return (ERR);
	converted_lst = doub_lstdup((void *)tokens_lst, ret_token_str, NULL);
	if (converted_lst == NULL)
	{
		free_environment_array(env);
		return (ERR);
	}
	err = exec((void *)converted_lst, env, status);
	doub_lstdelall((void **) &converted_lst, NULL);
	free_environment_array(env);
	if (err && add_exit_status_as_env((void **)&env_lst, err))
		return (ERR);
	return (OK);
}

// this function does not allocate memory for the new token.
static void	*ret_token_str(void *node_data)
{
	t_token_data	*token_data;

	token_data = (t_token_data *)node_data;
	return ((void *)token_data->token_str);
}
