/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/24 15:57:39 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

// static void	put_tokens_lst(t_blst *tokens_lst);

int	parser(t_blst **tokens_lst)
{
	if (!syntax_checker(*tokens_lst, cmp_syntax))
		return (0);
	merge_redirects(tokens_lst);
	delete_quote(tokens_lst);
	delete_blank(tokens_lst);
	// put_tokens_lst(*tokens_lst);
	return (1);
}

// static void	put_tokens_lst(t_blst *tokens_lst)
// {
// 	t_blst			*tmp;
// 	t_token_data	*data;
// 	int				i;

// 	tmp = tokens_lst;
// 	i = 1;
// 	while (tmp->data != NULL)
// 	{
// 		data = tmp->data;
// 		printf("%d: text:%s, type:%d, sub:%d\n", i, data->token_str, data->token_type, data->sub_type);
// 		tmp = tmp->next;
// 		i++;
// 	}
// }
