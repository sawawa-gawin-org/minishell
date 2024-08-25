/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_blank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:58:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/25 15:09:22 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"


/**
 * @brief Deletes blank tokens from the tokens list.
 *
 * This function removes any blank tokens from the given tokens list.
 *
 * @param tokens_lst The address of the tokens list.
 */
void	delete_blank(t_blst **tokens_lst)
{
	t_blst			*sentinel;
	t_token_data	*data;

	sentinel = (*tokens_lst)->prev;
	while ((*tokens_lst)->u_data.token_data != NULL)
	{
		data = (*tokens_lst)->u_data.token_data;
		if (data->token_type == SPACE_FLAG)
			purge_token_node(tokens_lst);
		else
			(*tokens_lst) = (*tokens_lst)->next;
	}
	*tokens_lst = sentinel->next;
	return ;
}

void	purge_token_node(t_blst **lst)
{
	void	*purged;

	purged = doub_lstpurge((void **)lst);
	doub_lstdelone(purged, free_token_data);
}
