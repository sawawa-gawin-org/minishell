/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/02 22:41:00 by saraki           ###   ########.fr       */
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

int	parser(t_blst **tokens_lst, t_blst **env_lst) // change here
{
	int		err;

	delete_blank(tokens_lst);
	delete_quote(tokens_lst);
	err = parse_heredoc(tokens_lst);
	if (err == ERR)
		return (ERR);
	if (!expander(tokens_lst, env_lst))
		return (ERR);
	return (OK);
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
// 		printf("%d: text:%s, type:%d, sub:%d\n",
// 			i, data->token_str, data->token_type, data->sub_type);
// 		tmp = tmp->next;
// 		i++;
// 	}
// }
