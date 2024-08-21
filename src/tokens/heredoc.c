/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:41:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024/06/26 15:58:02 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static int	get_and_replace_delim(t_blst *now_node);
static char	*get_delimiter(t_blst *now_node);
static int	replace_delim_as_tok(char *delimiter_str, t_blst **delimiter_node);

// #Description
// Update the token string to the heredoc string.
// allocate the input string used `add_history`.
int	parse_heredoc(t_blst **tokens_lst)
{
	t_blst			*now_node;
	t_token_data	*data;
	int				err;

	now_node = *tokens_lst;
	while (now_node->u_data.token_data != NULL)
	{
		data = now_node->u_data.token_data;
		if (data->token_type == HEREDOC_FLAG)
		{
			err = get_and_replace_delim(now_node);
			if (err == ERR || err == ERR_SIGINT)
				return (err);
			now_node = now_node->next;
		}
		now_node = now_node->next;
	}
	return (OK);
}

static int	get_and_replace_delim(t_blst *now_node)
{
	char	*delimiter_str;
	int		err;

	delimiter_str = get_delimiter(now_node);
	if (delimiter_str == NULL)
		return (ERR);
	if (now_node->next->u_data.token_data->token_type == SPACE_FLAG)
		err = replace_delim_as_tok(delimiter_str, &(now_node->next->next));
	else
		err = replace_delim_as_tok(delimiter_str, &(now_node->next));
	free(delimiter_str);
	return (err);
}

static int	replace_delim_as_tok(char *delimiter_str,
		t_blst **delimiter_node)
{
	t_token_data	*delimiter_data;
	int				err;

	if (delimiter_str == NULL || delimiter_node == NULL
		|| *delimiter_node == NULL)
		return (ERR);
	delimiter_data = (*delimiter_node)->u_data.token_data;
	err = set_heredoc_string_to_node(delimiter_str, delimiter_data);
	return (err);
}

static char	*get_delimiter(t_blst *now_node)
{
	size_t	i;
	char	*delimiter_str;
	char	*ret;

	if (now_node->next->u_data.token_data->token_type == SPACE_FLAG)
		delimiter_str = now_node->next->next->u_data.token_data->token_str;
	else
		delimiter_str = now_node->next->u_data.token_data->token_str;
	i = 0;
	while (delimiter_str[i] != '\0' && delimiter_str[i] != '\n')
		i++;
	ret = ft_substr(delimiter_str, 0, i);
	if (ret == NULL)
		return (NULL);
	return (ret);
}
