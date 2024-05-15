/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/15 04:58:46 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

// static void	put_tokens_lst(t_blst *tokens_lst);

// # Description
// This function is the main parser function.
//
// exapmle:
// before
// ```c
// lst->data = "ls"
// lst->next->data = " "
// ...->next->data = "-la"
// ...->next->data = " "
// ...->next->data = " "
// ...->next->data = "|"
// ...->next->data = " "
// ...->next->data = "wc"
// ...->next->data = " "
// ...->next->data = "-l"
// ```
// after
// ```c
// lst->data = "ls"
// lst->next->data = " "
// ...->next->data = "-la"
// ...->next->data = "|"
// ...->next->data = "wc"
// ...->next->data = " "
// ...->next->data = "-l"
// ```

int	parser(t_blst **tokens_lst, t_blst **env_lst)
{
	if (!syntax_checker(*tokens_lst, cmp_syntax))
		return (0);
	merge_redirects(tokens_lst);
	delete_quote(tokens_lst);
	delete_blank(tokens_lst);
	// put_tokens_lst(*tokens_lst);
	if (!expander(tokens_lst, env_lst))
		return (0);
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
