/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:41:27 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/26 08:58:55 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static char	*get_delimiter(char *delimiter_str);
static int	replace_delimiter_as_token(char *delimiter, t_blst **delimiter_node);
static int	is_flag(char *heredoc_str, int type);
static char	*append_current_heredoc(
				char *source, t_blst *gain_node, char *delim_str);

// #Description
// Update the token string to the heredoc string.
char	*parse_heredoc(t_blst **tokens_lst)
{
	t_blst			*now_node;
	t_token_data	*data;
	char			*history;
	char			*delim_str;

	now_node = *tokens_lst;
	history = ft_calloc(1, sizeof(char));
	while (history != NULL && now_node->u_data.t_data != NULL)
	{
		data = now_node->u_data.t_data;
		if (data->token_type == HEREDOC_FLAG)
		{
			delim_str = get_delimiter(now_node->next->u_data.t_data->token_str);
			if (replace_delimiter_as_token(delim_str, &(now_node->next)) == ERR)
			{
				free(history);
				free(delim_str);
				return (NULL);
			}
			history = append_current_heredoc(history, now_node->next, delim_str);
			free(delim_str);
		}
		now_node = now_node->next;
	}
	return (history);  // ここがNULLならadd_historyに普通のlineが渡される。
	// historyはデリミタつき
}

static char	*append_current_heredoc(
				char *source, t_blst *gain_node, char *delim_str)
{
	char	*ret;
	char	*gain_str;
	size_t	total_len;

	gain_str = gain_node->u_data.t_data->token_str;
	total_len = ft_strlen(source); // << 付きの文章
	total_len += ft_strlen(gain_str); // << 付きの文章 + 得られた入力
	total_len += ft_strlen(delim_str) + 1; // << 付きの文章 + 得られた入力 + デリミタ + (改行)
	ret = ft_calloc(total_len + 1, sizeof(char));
	if (ret == NULL)
	{
		free(source);
		return (NULL);
	}
	ft_strlcat(ret, source, ft_strlen(source) + 1);
	free(source);
	ft_strlcat(ret, gain_str, ft_strlen(ret) + ft_strlen(gain_str) + 1);
	ft_strlcat(ret, delim_str, ft_strlen(ret) + ft_strlen(delim_str) + 1);
	ft_strlcat(ret, "\n", ft_strlen(ret) + 1 + 1);
	return (ret);
}

static int	replace_delimiter_as_token(char *delimiter_str, t_blst **delimiter_node)
{
	t_token_data	*delimiter_data;
	char			*heredoc_str;
	int				type;

	if (delimiter_str == NULL ||delimiter_node == NULL || *delimiter_node == NULL)
		return (ERR);
	delimiter_data = (*delimiter_node)->u_data.t_data;
	if (delimiter_data != NULL)
	{
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
	return (OK);
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
