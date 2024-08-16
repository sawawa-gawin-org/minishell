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

static char	*get_delimiter(char *delimiter_str);
static int	replace_delimiter_as_token(
				char *delimiter_str, t_blst **delimiter_node);

// #Description
// Update the token string to the heredoc string.
// allocate the input string used `add_history`.
int	parse_heredoc(t_blst **tokens_lst)
{
	t_blst			*now_node;
	t_token_data	*data;
	char			*delim_str;
	int				err;

	now_node = *tokens_lst;
	while (now_node->u_data.token_data != NULL)
	{
		data = now_node->u_data.token_data;
		if (data->token_type == HEREDOC_FLAG)
		{
			delim_str = get_delimiter(
					now_node->next->u_data.token_data->token_str);
			if (delim_str == NULL)
				return (ERR);
			err = replace_delimiter_as_token(delim_str, &(now_node->next));
			free(delim_str);
			if (err == ERR || err == ERR_SIGINT)
				return (err);
			now_node = now_node->next;
		}
		now_node = now_node->next;
	}
	return (OK);
}

static int	replace_delimiter_as_token(
				char *delimiter_str, t_blst **delimiter_node)
{
	t_token_data	*delimiter_data;
	int				err;

	if (delimiter_str == NULL
		|| delimiter_node == NULL || *delimiter_node == NULL)
		return (ERR);
	delimiter_data = (*delimiter_node)->u_data.token_data;
	err = set_heredoc_string_to_node(
			delimiter_str, delimiter_data);
	return (err);
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

void	update_token_str_data(
				t_token_data *target_data, char *new_token_str)
{
	int		type;	

	type = is_flag(new_token_str, target_data->token_type);
	free(target_data->token_str);
	target_data->token_str = new_token_str;
	target_data->token_type = type;
}

//data->token_typeとheredoc_strから、"$VAL"か'VAL'か"VAL"かを判断して、FLAGを割り当てる
// Need fix
int	is_flag(char *heredoc_str, int type) // Check later
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
