/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:50:29 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/16 08:43:39 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

// static int	find_contd_tube(t_blst *node);
// static int	find_contd_redirect(t_blst *node);
static int	next_token_is_specific_flag(int flag, t_blst *node);
static int	is_token_terminal(t_blst *node);
static char	*get_next_token_str(t_blst *node);

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
	while (ret_node->u_data.token_data != NULL)
	{
		if (cmp_f(ret_node->u_data.token_data, ret_node) != OK)
			return (0);
		ret_node = ret_node->next;
		i ++;
	}
	return (1);
}

// Syntax Error Cases
// Case 1: Type is TUBE at the beginning of the token
// {|, ...}

// Case 2: Type is TUBE at the current position and the next token's
// 	type is also TUBE
// {..., |, |, ...}

// Case 3: A metacharacter appears after a metacharacter excluding tu
// - be.
// {..., >, |, ...}, {..., >, >, ...}, {..., >, |, ...},...etc

// Case 4: Type is a redirection at the current position, and next is
//  NULL
// {..., >}, {..., >>}, {..., <}, {..., <<}

// Case 5: Type is OPEN_QUOTE at the current position
// {..., \", ...}
// TODO: ADD ERR MSG
// TOKEN = {"|", "<", ">", ">>", "<<", "newline"}
// minishell: syntax error near unexpected token `TOKEN'

// The following code represents each case.
// syntax_unexpected_error("|"); // case 1
// syntax_unexpected_error("|"); // case 2
// syntax_unexpected_error("newline"); // case 3
// syntax_unexpected_error(get_next_token_str(node->next)); // case 3
// syntax_unexpected_error("newline"); // case 4
// syntax_unclose_quote_error(); 

// TEST Cases
// $ >|
// bash: syntax error near unexpected token `newline'
// $ >>|
// bash: syntax error near unexpected token `|'
// $ <|
// bash: syntax error near unexpected token `|'
// $ <<|
// bash: syntax error near unexpected token `|'
// $ > |
// bash: syntax error near unexpected token `|'
// $ >> |
// bash: syntax error near unexpected token `|'
// $ < |
// bash: syntax error near unexpected token `|'
// $ << |
// bash: syntax error near unexpected token `|'

/**
 * @brief Compares the syntax of two elements.
 *
 * This function is used to compare the syntax of two elements. It takes two
 * pointers as arguments and returns an integer value indicating the result of
 * the comparison.
 *
 * @param d A pointer to the first element to compare.
 * @param n A pointer to the second element to compare.
 * @return An integer value indicating the result of the comparison.
 * @note
 */
int	cmp_syntax(void *d, void *n)
{
	t_token_data	*data;
	t_blst			*node;

	data = d;
	node = n;
	if (node->prev->u_data.token_data == NULL && (data->token_type & TUBE_FLAG))
		return (syntax_unexpected_error("|"));
	if (node->next->u_data.token_data != NULL)
	{
		if ((data->token_type & TUBE_FLAG)
			&& next_token_is_specific_flag(TUBE_FLAG, node->next))
			return (syntax_unexpected_error("|"));
		else if (data->token_type & GREAT_FLAG
			&& node->next->u_data.token_data->token_type & TUBE_FLAG)
			return (syntax_unexpected_error("newline"));
		else if ((data->token_type & (META_FLAG & (~TUBE_FLAG)))
			&& next_token_is_specific_flag(META_FLAG, node->next))
			return (syntax_unexpected_error(get_next_token_str(node->next)));
	}
	if ((data->token_type & META_FLAG) && is_token_terminal(node->next))
		return (branching_syntax_err_by_flag(data->token_type));
	if (data->token_type & OPEN_QUOTE_FLAG)
		return (syntax_unclose_quote_error());
	return (OK);
}

static int	next_token_is_specific_flag(int flag, t_blst *node)
{
	t_token_data	*data;

	while (node->u_data.token_data != NULL)
	{
		data = node->u_data.token_data;
		if (data->token_type & flag)
			return (1);
		else if (data->token_type & SPACE_FLAG)
			node = node->next;
		else
			break ;
	}
	return (0);
}

// Returns 1 if the token is the end
static int	is_token_terminal(t_blst *node)
{
	t_token_data	*data;

	while (node->u_data.token_data != NULL)
	{
		data = node->u_data.token_data;
		if (data->token_type & (~SPACE_FLAG))
			return (0);
		else if (data->token_type & SPACE_FLAG)
			node = node->next;
		else
			break ;
	}
	return (1);
}

static char	*get_next_token_str(t_blst *node)
{
	while (node->u_data.token_data != NULL
		&& node->u_data.token_data->token_type & SPACE_FLAG)
		node = node->next;
	return (node->u_data.token_data->token_str);
}
