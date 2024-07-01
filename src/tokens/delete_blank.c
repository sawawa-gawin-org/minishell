/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_blank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:58:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/06/26 14:51:51 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static void	purge(t_blst **lst);

// Description:
// Drop all the spaces token in the tokens list.
void	delete_blank(t_blst **tokens_lst)
{
	t_blst			*head;
	t_token_data	*data;

	head = *tokens_lst;
	while ((*tokens_lst)->u_data.token_data != NULL)
	{
		data = (*tokens_lst)->u_data.token_data;
		if (data->token_type == SPACE_FLAG)
			purge(tokens_lst);
		else
			(*tokens_lst) = (*tokens_lst)->next;
	}
	*tokens_lst = head;
}

static void	purge(t_blst **lst)
{
	void	*purged;

	purged = doub_lstpurge((void **)lst);
	doub_lstdelone(purged, free_token_data);
}
