/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bridge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:24:11 by saraki            #+#    #+#             */
/*   Updated: 2024/09/15 09:02:48 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"
#include "common.h"
#include "env.h"
#include "dbllst.h"

static void	*ret_token_str(void *data);

/**
 * Executes the commands in the given tokens list.
 *
 * @param tokens_lst The list of tokens representing the commands.
 * @param env_lst    The list of environment variables.
 * @param status     A pointer to the status variable.
 * @return           Returns an integer indicating the execution status.
 */
int	exec_tokenslst_cmds(t_blst *tokens_lst, t_blst **env_lst, int *status)
{
	// void	*converted_lst;
	char	**env;

	env = create_env_arr_from_lst(*env_lst, 0);
	if (env == NULL)
		return (ERR);
	// converted_lst = doub_lstdup((void *)tokens_lst, ret_token_str, NULL);
	// if (converted_lst == NULL)
	// {
	// 	free_environment_array(env);
	// 	return (ERR);
	// }
	*status = exec((t_tokenlst **) &tokens_lst, env, env_lst);
	// doub_lstdelall((void **) &converted_lst, NULL);
	free_environment_array(env);
	return (OK);
}

// /// @brief this function does not allocate memory for the new token.
// static void	*ret_token_str(void *node_data)
// {
// 	t_token_data	*token_data;

// 	token_data = (t_token_data *)node_data;
// 	return ((void *)token_data->token_str);
// }
