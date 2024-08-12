/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:35:20 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/12 06:24:15 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static int	expand_env(t_blst *tokens_lst, t_blst *env_lst);
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
	if (!expand_env(*tokens_lst, env_lst))
		return (0);
	return (1);
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
static int	expand_env(t_blst *tokens_lst, t_blst *env_lst)
{
	while (tokens_lst->u_data.token_data != NULL)
	{
		if (is_expandable_token_type(tokens_lst->u_data.token_data))
		{
			if (!expand_env_as_str(tokens_lst->u_data.token_data, env_lst))
				return (0);
		}
		tokens_lst = tokens_lst->next;
	}
	return (1);
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
