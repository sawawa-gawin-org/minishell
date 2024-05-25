/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bridge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:24:11 by saraki            #+#    #+#             */
/*   Updated: 2024/05/16 18:30:31 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"
#include "exec.h"

static void	*ret_token_str(void *data);

int	exec_tokenslst_cmds(t_blst *tokens_lst)
{
	void	*converted_lst;
	int		err;

	converted_lst = doub_lstdup((void *)tokens_lst, ret_token_str, NULL);
	if (converted_lst == NULL)
		return (ERR);
	err = exec((void *)converted_lst);
	doub_lstdelall((void **) &converted_lst, NULL);
	if (err)
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
