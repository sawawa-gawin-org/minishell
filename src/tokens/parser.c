/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/09/15 05:26:09 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

// static int	is_echo(t_blst *tokens_lst);
// static int	echo_parser(t_blst **tokens_lst);
// static int	concat_token_str(t_blst *token_node);

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

static int	expantion(t_blst **tokens_lst, t_blst *env_lst);
static int	re_tokenize(t_blst **tokens_lst);
static void	inject_nodes(t_blst **replaced_node, t_blst *inject_nodes);
static int	is_expandable_token_type(t_token_data *data);

int	parser(t_blst **tokens_lst, t_blst **env_lst)
{
	int		err;

	delete_quote(tokens_lst);
	err = parse_heredoc(tokens_lst);
	if (err == ERR)
		return (ERR);
	err = expantion(tokens_lst, *env_lst);
	if (err != OK)
		return (err);
	if (concat_consecutive_tokens_node(tokens_lst))
		return (ERR);
	delete_blank(tokens_lst);
	return (OK);
}

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
static int	expantion(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*data;
	int				err;

	err = OK;
	while ((*tokens_lst)->u_data.token_data != NULL)
	{
		data = (*tokens_lst)->u_data.token_data;
		if (is_expandable_token_type(data) && err == OK)
		{
			err = expand_parameter(tokens_lst, env_lst);
			if (err == OK && data->token_type == VAL_FLAG
				&& ft_strcmp(data->token_str, "") == 0)
				purge_token_node(tokens_lst);
			else if (err == OK && data->token_type == VAL_FLAG)
				err = re_tokenize(tokens_lst);
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
			|| data->token_type == DOUBLE_QUOTE_VAL_FLAG
			|| data->token_type == HEREDOC_EXPANDABLE_FLAG))
		return (1);
	return (0);
}

// # echo parser node
// int	parser(t_blst **tokens_lst, t_blst **env_lst)
// {
// 	int		err;

// 	err = OK;
// 	if (is_echo(*tokens_lst))
// 		err = echo_parser(&((*tokens_lst)->next));
// 	if (err != OK)
// 		return (err);
// 	delete_blank(tokens_lst);
// 	delete_quote(tokens_lst);
// 	err = parse_heredoc(tokens_lst);
// 	if (err != OK)
// 		return (ERR);
// 	if (!expander(tokens_lst, *env_lst))
// 		return (ERR);
// 	return (OK);
// }

// static int	echo_parser(t_blst **tokens_lst)
// {
// 	int				err;
// 	t_blst			*now_node;
// 	t_token_data	*data;

// 	err = OK;
// 	now_node = *tokens_lst;
// 	data = now_node->u_data.token_data;
// 	while (data != NULL && (data->token_type == SPACE_FLAG
// 			|| ft_strcmp(data->token_str, "-n") == 0))
// 	{
// 		now_node = now_node->next;
// 		data = now_node->u_data.token_data;
// 	}
// 	while (data != NULL)
// 	{
// 		if (data->token_type == TOKEN_FLAG)
// 			err = concat_token_str(now_node);
// 		if (err != OK)
// 			break ;
// 		now_node = now_node->next;
// 		data = now_node->u_data.token_data;
// 	}
// 	return (err);
// }

// // echo| |(-n)| |hello| |world|"quote"|name| |is| |'42'|NULL
// //                now (rewrited_node)
// static int	concat_token_str(t_blst *rewrited_node)
// {
// 	t_blst			*now_node;
// 	t_token_data	*data;
// 	char			*new_str;

// 	new_str = ft_strdup(rewrited_node->u_data.token_data->token_str);
// 	if (new_str == NULL)
// 		return (ERR_ALLOCATE_MEMORY);
// 	now_node = rewrited_node->next;
// 	data = now_node->u_data.token_data;
// 	while (data != NULL && (data->token_type == SPACE_FLAG
// 			|| data->token_type == TOKEN_FLAG))
// 	{
// 		new_str = strjoin_allfree(new_str, data->token_str);
// 		if (new_str == NULL)
// 			return (ERR_ALLOCATE_MEMORY);
// 		data->token_str = NULL;
// 		purge_token_node(&now_node);
// 		data = now_node->u_data.token_data;
// 	}
// 	free(rewrited_node->u_data.token_data->token_str);
// 	rewrited_node->u_data.token_data->token_str = new_str;
// 	rewrited_node->u_data.token_data->token_type = TOKEN_FLAG;
// 	rewrited_node->u_data.token_data->sub_type = TOKEN_FLAG;
// 	return (OK);
// }

// static int	is_echo(t_blst *tokens_lst)
// {
// 	t_token_data	*data;

// 	data = tokens_lst->u_data.token_data;
// 	if (data->token_type == TOKEN_FLAG
// 		&& ft_strcmp(data->token_str, "echo") == 0)
// 		return (1);
// 	return (0);
// }
