/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/14 12:35:26 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static int	concat_consecutive_tokens_node(t_blst **tokens_lst);
static int	join_consecutive_token(t_blst *now, t_blst **next);
static int	is_consecutive_type(int token_type);

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

int	parser(t_blst **tokens_lst, t_blst **env_lst)
{
	int		err;

	delete_quote(tokens_lst);
	if (concat_consecutive_tokens_node(tokens_lst))
		return (ERR);
	delete_blank(tokens_lst);
	err = parse_heredoc(tokens_lst);
	if (err != OK)
		return (ERR);
	if (!expander(tokens_lst, *env_lst))
		return (ERR);
	return (OK);
}

static int	concat_consecutive_tokens_node(t_blst **tokens_lst)
{
	t_blst			*now;
	t_blst			*next;

	now = *tokens_lst;
	while (now->u_data.token_data != NULL)
	{
		next = now->next;
		if (next->u_data.token_data == NULL)
			break ;
		if (is_consecutive_type(now->u_data.token_data->token_type)
			&& is_consecutive_type(next->u_data.token_data->token_type))
		{
			if (join_consecutive_token(now, &next))
				return (ERR_ALLOCATE_MEMORY);
		}
		else
			now = now->next;
	}
	return (OK);
}

static int	join_consecutive_token(t_blst *now, t_blst **next)
{
	char	*str1;
	char	*str2;
	char	*new_str;

	str1 = now->u_data.token_data->token_str;
	str2 = (*next)->u_data.token_data->token_str;
	new_str = ft_strjoin(str1, str2);
	if (new_str == NULL)
		return (ERR_ALLOCATE_MEMORY);
	free(str1);
	now->u_data.token_data->token_str = new_str;
	purge_token_node(next);
	return (OK);
}

static int	is_consecutive_type(int token_type)
{
	if (token_type == TOKEN_FLAG
		|| (token_type >= DOUBLE_QUOTE_FLAG && token_type <= VAL_FLAG))
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
