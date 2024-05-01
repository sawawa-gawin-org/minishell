/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_blank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:58:53 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/01 15:50:43 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_int.h"

static void	purge(t_blst **lst);

// パイプ前後のスペースの削除と終端前のスペースの削除
void	delete_blank(t_blst **tokens_lst)
{
	t_token_data	*data;
	t_token_data	*next_data;

	while ((*tokens_lst)->data != NULL)
	{
		data = (*tokens_lst)->data;
		next_data = (*tokens_lst)->next->data;
		if (data->token_type == SPACE_FLAG \
			&& (next_data == NULL || next_data->token_type == TUBE_FLAG))
			purge(tokens_lst);
		else if ((data->token_type == TUBE_FLAG \
			|| data->sub_type == HEREDOC_QUOTE_FLAG \
			|| (LESS_FLAG <= data->sub_type && data->sub_type <= APPEND_FLAG)) \
			&& next_data->token_type == SPACE_FLAG)
		{
			(*tokens_lst) = (*tokens_lst)->next;
			purge(tokens_lst);
		}
		else
			(*tokens_lst) = (*tokens_lst)->next;
	}
	while ((*tokens_lst)->prev->data != NULL)
		(*tokens_lst) = (*tokens_lst)->prev;
}

static void	purge(t_blst **lst)
{
	void	*purged;

	purged = doub_lstpurge((void **)lst);
	doub_lstdelone(purged, free_token_data);
}
