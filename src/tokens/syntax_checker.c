/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:50:29 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/12 09:20:36 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

// static int	find_contd_tube(t_blst *node);
// static int	find_contd_redirect(t_blst *node);
static int	next_token_is_specific_flag(int flag, t_blst *node);

// # Description
// This function checks the syntax of the tokens list.
// - syntax_ok=1
// - syntax_error=0
int	syntax_checker(t_blst *lst, t_cmp_f cmp_f)
{
	t_blst	*ret_node;
	int		i;

	if (lst == NULL)
		return (0);
	i = 0;
	ret_node = lst;
	while (ret_node->u_data.t_data != NULL)
	{
		if (cmp_f(ret_node->u_data.t_data, ret_node))
			return (0);
		ret_node = ret_node->next;
		i ++;
	}
	return (1);
}

// Syntax Error Cases
// Case 1: Type is TUBE at the beginning of the token
// {|, ...}
//
// Case 2: Type is TUBE at the current position and the next token's
// 	type is also TUBE
// {..., |, |, ...}
//
// Case 3: A metacharacter appears after a metacharacter excluding tu
// - be.
// {..., >, |, ...}, {..., >, >, ...}, {..., >, |, ...},...etc
//
// Case 4: Type is a redirection or TUBE at the current position, an
// 	-d next is NULL
// {..., >}, {..., >>}, {..., <}, {..., <<}
//
// Case 5: Type is OPEN_QUOTE at the current position
// {..., "}
// TODO: ADD ERR MSG
// minishell: syntax error near unexpected token `{"|", "<", ">", ">>", "<<"}'
int	cmp_syntax(void *d, void *n)
{
	t_token_data	*data;
	t_blst			*node;

	data = d;
	node = n;
	if (node->prev->u_data.t_data == NULL && (data->token_type & TUBE_FLAG))
		return (printf("case 1\n"), 1);
	if (node->next->u_data.t_data != NULL)
	{
		if ((data->token_type & TUBE_FLAG)
			&& next_token_is_specific_flag(TUBE_FLAG, node->next))
			return (printf("case 2\n"), 1);
		else if ((data->token_type & (META_FLAG & (~TUBE_FLAG)))
			&& next_token_is_specific_flag(META_FLAG, node->next))
			return (printf("case 3\n"), 1);
	}
	else if (data->token_type & (META_FLAG & (~TUBE_FLAG)))
		return (printf("case 4\n"), 1);
	if (data->token_type & OPEN_QUOTE_FLAG)
		return (printf("case 5\n"), 1);
	return (0);
}

static int	next_token_is_specific_flag(int flag, t_blst *node)
{
	t_token_data	*data;

	while (node->u_data.t_data != NULL)
	{
		data = node->u_data.t_data;
		if (data->token_type & flag)
			return (1);
		else if (data->token_type & SPACE_FLAG)
			node = node->next;
		else
			break ;
	}
	if (node->u_data.t_data == NULL)
		return (1);
	return (0);
}

// static int	find_contd_tube(t_blst *node)
// {
// 	t_token_data	*data;

// 	while (node->u_data.t_data != NULL)
// 	{
// 		data = node->u_data.t_data;
// 		if (data->token_type == TUBE_FLAG)
// 			return (1);
// 		else if (data->token_type == SPACE_FLAG)
// 			node = node->next;
// 		else
// 			break ;
// 	}
// 	if (node->u_data.t_data == NULL)
// 		return (1);
// 	return (0);
// }

// static int	find_contd_redirect(t_blst *node)
// {
// 	t_token_data	*data;

// 	while (node->u_data.t_data != NULL)
// 	{
// 		data = node->u_data.t_data;
// 		if (TUBE_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
// 			return (1);
// 		else if (data->token_type == SPACE_FLAG)
// 			node = node->next;
// 		else
// 			break ;
// 	}
// 	if (node->u_data.t_data == NULL)
// 		return (1);
// 	return (0);
// }