/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/23 18:48:15 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static void	put_tokens_lst(t_blst *tokens_lst);

int	parser(t_blst **tokens_lst)
{
	if (!syntax_checker(*tokens_lst, cmp_syntax))
		return (0);
	// format_tokenlst(tokens_lst);
	// if (!heredoc_put(tokens_lst))
	// 	return (0);
	put_tokens_lst(*tokens_lst);
	return (1);
}

static void	put_tokens_lst(t_blst *tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;

	tmp = tokens_lst;
	while (tmp->data != NULL)
	{
		data = tmp->data;
		printf("text:%s, type:%d, sub:%d\n", data->token_str, data->token_type, data->sub_type);
		tmp = tmp->next;
	}
}
