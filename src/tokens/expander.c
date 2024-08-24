/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:35:20 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/16 13:42:36 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static void	inject_nodes(t_blst **replaced_node, t_blst *inject_nodes);
static int	re_tokenize(t_blst **tokens_lst);
static int	is_expandable_token_type(t_token_data *data);
static int	find_illegal_blank(char *str);

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
 * @note Expandable token type: VAL_FLAG, DOUBLE_QUOTE_VAL_FLAG,
 * !HEREDOC_FLAG, !HEREDOC_QUOTE_FLAG
 */
int	expander(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*data;
	int				err;

	err = OK;
	while ((*tokens_lst)->u_data.token_data != NULL)
	{
		data = (*tokens_lst)->u_data.token_data;
		if (is_expandable_token_type(data) && err == OK)
		{
			err = expand_and_check_ambiguous(tokens_lst, env_lst);
			if (data->token_type != DOUBLE_QUOTE_VAL_FLAG
				&& find_illegal_blank(data->token_str) != OK)
			{
				purge_token_node(tokens_lst);
				continue ;
			}
			if (re_tokenize(tokens_lst))
				return (ERR);
		}
		(*tokens_lst) = (*tokens_lst)->next;
	}
	(*tokens_lst) = (*tokens_lst)->next;
	if (err != OK)
		return (err);
	return (OK);
}

static int	re_tokenize(t_blst **tokens_lst)
{
	t_blst	*updated_node;
	char	*replaced_str;

	replaced_str = (*tokens_lst)->u_data.token_data->token_str;
	if (ft_strcmp(replaced_str, "") == 0)
		return (OK);
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

static int	find_illegal_blank(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && is_blank(str[i]))
		i++;
	if (str[i] == '\0')
		return (ERR);
	return (OK);
}
