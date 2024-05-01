/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:50:29 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/01 15:56:17 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static int	find_contd_tube(t_blst *node);
static int	find_contd_redirect(t_blst *node);

//syntax_ok=1
int	syntax_checker(t_blst *lst, t_cmp_f cmp_f)
{
	t_blst	*ret_node;
	int		i;

	if (lst == NULL)
		return (0);
	i = 0;
	ret_node = lst;
	while (ret_node->data != NULL)
	{
		if (cmp_f(ret_node->data, ret_node))
			return (0);
		ret_node = ret_node->next;
		i ++;
	}
	return (1);
}

//SyntaxErrorCases
//case1. 先頭のtokenでtypeがTUBE
//case2. 現在typeがTUBEで次tokenのtypeがTUBE
//case3. 現在typeがリダイレクトのどれかで次typeがTUBE
//case4. 現在typeがリダイレクトのどれかで次typeもリダイレクト
//case5. 現在typeがリダイレクトまたはTUBEで、nextがNULL
//case6. 現在typeがOPEN_QUOTE
int	cmp_syntax(void *d, void *n)
{
	t_token_data	*data;
	t_blst			*node;

	data = d;
	node = n;
	if (node->prev->data == NULL && data->token_type == TUBE_FLAG)
		return (printf("A\n"), 1);
	if ((t_token_data *)node->next->data != NULL)
	{
		if (data->token_type == TUBE_FLAG)
			if (find_contd_tube(node->next))
				return (printf("B\n"), 1);
		if (LESS_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
			if (find_contd_redirect(node->next))
				return (printf("C\n"), 1);
	}
	else
		if (TUBE_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
			return (printf("D\n"), 1);
	if (data->token_type == OPEN_QUOTE_FLAG)
		return (printf("E\n"), 1);
	return (0);
}

static int	find_contd_tube(t_blst *node)
{
	t_token_data	*data;

	while (node->data != NULL)
	{
		data = node->data;
		if (data->token_type == TUBE_FLAG)
			return (1);
		else if (data->token_type == SPACE_FLAG)
			node = node->next;
		else
			break ;
	}
	if (node->data == NULL)
		return (1);
	return (0);
}

static int	find_contd_redirect(t_blst *node)
{
	t_token_data	*data;

	while (node->data != NULL)
	{
		data = node->data;
		if (TUBE_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
			return (1);
		else if (data->token_type == SPACE_FLAG)
			node = node->next;
		else
			break ;
	}
	if (node->data == NULL)
		return (1);
	return (0);
}
