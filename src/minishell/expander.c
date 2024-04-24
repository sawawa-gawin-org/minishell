/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:35:20 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/24 16:39:34 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

static void	put_tokens_lst(t_blst *tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;
	int				i;

	tmp = tokens_lst;
	i = 1;
	while (tmp->data != NULL)
	{
		data = tmp->data;
		printf("%d: text:%s, type:%d, sub:%d\n", i, data->token_str, data->token_type, data->sub_type);
		tmp = tmp->next;
		i++;
	}
}

int	expander(t_blst **tokens_lst)
{
	put_tokens_lst(*tokens_lst);
	return (1);
}
