/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/22 21:59:14 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static void	put_tokens_lst(t_blst **tokens_lst);

void	test_purge(t_blst **tokens_lst)
{
	void	*tmp;

	tmp = doub_lstpurge((void **)tokens_lst);
	doub_lstdelone(tmp, free_token_data);
}

void	middle(t_blst **tokens_lst)
{
	test_purge(tokens_lst);
}

int	parser(t_blst **tokens_lst)
{
	if (!syntax_checker(*tokens_lst, cmp_syntax))
		return (0);
	// test_purge(tokens_lst);
	middle(tokens_lst);
	// delete_quote(tokens_lst);
	// delete_blank(tokens_lst);
	// if (!heredoc_put(tokens_lst))
	// 	return (0);
	put_tokens_lst(tokens_lst);
	return (1);
}

static void	put_tokens_lst(t_blst **tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;

	tmp = *tokens_lst;
	while (tmp->data != NULL)
	{
		data = tmp->data;
		printf("text:%s, type:%d\n", data->token_str, data->token_type);
		tmp = tmp->next;
	}
	printf("fin\n");
}
