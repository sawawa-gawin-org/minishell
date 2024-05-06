/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 07:33:25 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/06 15:22:18 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static void	process_token_length(t_blst **lst);
static void	replace_noquote(char *str, int len);

void	delete_quote(t_blst **tokens_lst)
{
	t_token_data	*data;

	data = (*tokens_lst)->data.t_data;
	while ((*tokens_lst)->data.t_data != NULL)
	{
		data = (*tokens_lst)->data.t_data;
		if (DOUBLE_QUOTE_FLAG <= data->token_type
			&& data->token_type <= SINGLE_QUOTE_FLAG)
		{
			process_token_length(tokens_lst);
			continue ;
		}
		*tokens_lst = (*tokens_lst)->next;
	}
	while ((*tokens_lst)->prev->data.t_data != NULL)
		*tokens_lst = (*tokens_lst)->prev;
}

static void	process_token_length(t_blst **lst)
{
	int				len;
	void			*purged;
	t_token_data	*data;

	data = (*lst)->data.t_data;
	len = ft_strlen(data->token_str);
	if (len == 2)
	{
		purged = doub_lstpurge((void **)lst);
		doub_lstdelone(purged, free_token_data);
	}
	else if (2 < len && data->token_str[0] == data->token_str[len - 1])
	{
		replace_noquote(data->token_str, len);
		*lst = (*lst)->next;
	}
}

static void	replace_noquote(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len - 2)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
}
