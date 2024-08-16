/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:35:20 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/16 08:37:40 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static int	expand_env(t_blst **tokens_lst, t_blst *env_lst);
static void	inject_nodes(t_blst **replaced_node, t_blst *inject_nodes);
static int	re_tokenize(t_blst **tokens_lst);
static int	is_expandable_token_type(t_token_data *data);

/**
 * Expands tokens in the given list using the environment variables.
 *
 * @param tokens_lst A pointer to the list of tokens to be expanded.
 * @param env_lst A pointer to the list of environment variables.
 * @return The number of tokens expanded.
 * @details confirm `man bash` ("EXPANSION")
 * @note Quote Removal:	After the preceding expansions,
 * all unquoted occurrences of the characters \, ', and "  that
 * did not result from one of the above	expansions are removed.
 */
int	expander(t_blst **tokens_lst, t_blst *env_lst)
{
	if (expand_env(tokens_lst, env_lst))
		return (ERR);
	return (OK);
}

/**
 * Expands environment variables in the given token list.
 *
 * @param tokens_lst The list of tokens to expand.
 * @param env_lst The list of environment variables.
 * @return The number of expanded tokens.
 * @note expandable token type: VAL_FLAG, DOUBLE_QUOTE_VAL_FLAG,
 * !HEREDOC_FLAG, !HEREDOC_QUOTE_FLAG
 */
static int	expand_env(t_blst **tokens_lst, t_blst *env_lst)
{
	while ((*tokens_lst)->u_data.token_data != NULL)
	{
		if (is_expandable_token_type((*tokens_lst)->u_data.token_data))
		{
			if (!expand_env_as_str((*tokens_lst)->u_data.token_data, env_lst))
				return (ERR);
			if (re_tokenize(tokens_lst))
				return (ERR);
		}
		(*tokens_lst) = (*tokens_lst)->next;
	}
	(*tokens_lst) = (*tokens_lst)->next;
	return (OK);
}

static	int	re_tokenize(t_blst **tokens_lst)
{
	t_blst	*updated_node;
	char	*replaced_str;

	replaced_str = (*tokens_lst)->u_data.token_data->token_str;
	updated_node = tokenizer(&replaced_str);
	if (updated_node == NULL)
		return (ERR);
	inject_nodes(tokens_lst, updated_node);
	return (OK);
}

static void	inject_nodes(t_blst **replaced_node, t_blst *inject_nodes)
{
	t_blst	*inject_tirminator;
	t_blst	*inject_last_node;
	t_blst	*left_connected_node;
	t_blst	*right_connected_node;

	inject_tirminator = inject_nodes->prev;
	purge_token_node(&inject_tirminator);
	inject_last_node = inject_tirminator->prev;
	purge_token_node(replaced_node);
	left_connected_node = (*replaced_node)->prev;
	right_connected_node = (*replaced_node);
	left_connected_node->next = inject_nodes;
	inject_nodes->prev = left_connected_node;
	right_connected_node->prev = inject_last_node;
	inject_last_node->next = right_connected_node;
	*replaced_node = inject_last_node;
	return ;
}

static int	is_expandable_token_type(t_token_data *data)
{
	if ((data->token_type == VAL_FLAG
			|| data->token_type == DOUBLE_QUOTE_VAL_FLAG)
		&& (data->sub_type != HEREDOC_FLAG
			&& data->sub_type != HEREDOC_QUOTE_FLAG))
		return (1);
	return (0);
}
