/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:41:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024/06/08 04:44:15 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static char	*get_delimiter(char *delimiter_str);
static char	*replace_delimiter_as_token(
				char *delimiter, t_blst **delimiter_node);
static int	is_flag(char *heredoc_str, int type);

// #Description
// Update the token string to the heredoc string.
// allocate the input string used `add_history`.
int	parse_heredoc(t_blst **tokens_lst, char **history)
{
	t_blst			*now_node;
	t_token_data	*data;
	char			*delim_str;
	int				is_inclued_heredoc;

	now_node = *tokens_lst;
	is_inclued_heredoc = 0;
	while (now_node->u_data.t_data != NULL)
	{
		data = now_node->u_data.t_data;
		if (data->token_type == HEREDOC_FLAG)
		{
			is_inclued_heredoc = 1;
			delim_str = get_delimiter(now_node->next->u_data.t_data->token_str);
			*history = replace_delimiter_as_token(delim_str, &(now_node->next)); // allocation
			free(delim_str);
			if (*history == NULL)
				return (NULL);
		}
		now_node = now_node->next;
	}
	return (is_inclued_heredoc);
}

static char	*replace_delimiter_as_token(
				char *delimiter_str, t_blst **delimiter_node)
{
	t_token_data	*delimiter_data;
	char			*heredoc_str;
	int				flag;
	int				type;

	flag = OK;
	if (delimiter_str == NULL ||delimiter_node == NULL || *delimiter_node == NULL)
		return (ERR);
	delimiter_data = (*delimiter_node)->u_data.t_data;
	if (delimiter_data != NULL)
	{
		if (ft_strcmp(delimiter_str, delimiter_data->token_str) != 0)
			flag = 1;
		heredoc_str = get_heredoc_input(delimiter_str, (*delimiter_node)->u_data.t_data->token_str);
		if (heredoc_str == NULL)
			return (ERR);
		type = is_flag(heredoc_str, delimiter_data->token_type);
		free(delimiter_data->token_str);
		delimiter_data->token_str = heredoc_str;
		delimiter_data->token_type = type;
	}
	else
		return (ERR);
	return (flag);
}

static char	*get_delimiter(char *delimiter_str)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (delimiter_str[i] != '\0' && delimiter_str[i] != '\n')
		i++;
	ret = ft_substr(delimiter_str, 0, i);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

//data->token_typeとheredoc_strから、"$VAL"か'VAL'か"VAL"かを判断して、FLAGを割り当てる
// Need fix
static int	is_flag(char *heredoc_str, int type)
{
	if (type == SINGLE_QUOTE_FLAG)
		return (SINGLE_QUOTE_FLAG);
	else
	{
		if (is_val(heredoc_str))
			return (DOUBLE_QUOTE_VAL_FLAG);
		else
			return (DOUBLE_QUOTE_FLAG);
	}
}
