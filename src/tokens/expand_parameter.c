/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:07:46 by syamasaw          #+#    #+#             */
/*   Updated: 2024/09/15 17:37:20 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static int	expand_env_as_str(t_token_data *tokendata, t_blst *env_lst);
static int	overwite_token_str(
				t_token_data *token, char *buff, int now, int old);
static int	check_ambigious_redir(t_blst *tokens_lst);
static int	find_illegal_blank(char *str);

// GENERAL_ERR: bash error
// ERR: malloc error
int	expand_parameter(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*data;
	char			*string_before_expantion;

	data = (*tokens_lst)->u_data.token_data;
	string_before_expantion = ft_strdup(data->token_str);
	if (string_before_expantion == NULL)
		return (ERR);
	if (expand_env_as_str(data, env_lst) == ERR)
		return (ERR);
	if (find_illegal_blank(data->token_str) != OK
		&& data->token_type != DOUBLE_QUOTE_VAL_FLAG)
	{
		if (check_ambigious_redir((*tokens_lst)->prev) != OK)
		{
			free(data->token_str);
			data->token_type = AMBIGUOUS_REDIRECTION_FLAG;
			data->token_str = string_before_expantion;
			return (OK);
		}
	}
	free(string_before_expantion);
	return (OK);
}

static int	check_ambigious_redir(t_blst *tokens_lst)
{
	t_token_data	*data;

	while (tokens_lst->u_data.token_data != NULL)
	{
		data = tokens_lst->u_data.token_data;
		if (data->token_type & SPACE_FLAG)
			tokens_lst = tokens_lst->prev;
		else if (data->token_type & (LESS_FLAG | GREAT_FLAG | APPEND_FLAG))
			return (ERR);
		else
			break ;
	}
	return (OK);
}

static int	find_illegal_blank(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && is_blank(str[i]))
		i++;
	if (str[i] == '\0')
		return (ERR);
	while (str[i] != '\0' && !is_blank(str[i]))
		i++;
	if (str[i] == '\0')
		return (OK);
	while (str[i] != '\0')
	{
		if (!is_blank(str[i]))
			return (ERR);
		i++;
	}
	return (OK);
}

static int	expand_env_as_str(t_token_data *tokendata, t_blst *env_lst)
{
	t_indexes		index;
	char			*buff;

	index.now = 0;
	index.old = 0;
	buff = (char *)ft_calloc(1, sizeof(char));
	if (!buff)
		return (ERR);
	while (tokendata->token_str[index.now] != '\0')
	{
		if (tokendata->token_str[index.now] == '$'
			&& tokendata->token_str[index.now + 1] != '\0'
			&& tokendata->token_str[index.now + 1] != '$')
		{
			buff = add_val_to_str(tokendata->token_str, buff, &index, env_lst);
			if (!buff)
				return (ERR);
			index.now += 1 + get_val_len(tokendata->token_str, index.now + 1);
			index.old = index.now;
		}
		else
			index.now += 1;
	}
	return (overwite_token_str(tokendata, buff, index.now, index.old));
}

// Description
// - if statement:
// 	when the environment varialbes are contained in a node.
// ie) `echo "$HOME aaaaaaaa"`
// - else statement:
// 	when the only environment varialbes are contained in a
// 	node, or the last string of node.
// ie) `echo "$HOME" or echo "aaaaaaa $HOME"`
static int	overwite_token_str(
				t_token_data *token, char *buff, int now, int old)
{
	char	*new_str;

	if (token->token_str[now] == '\0' && old < now)
	{
		new_str = strjoin_allfree(buff,
				ft_substr(token->token_str, old, now - old));
		if (new_str == NULL)
			return (ERR);
		free(token->token_str);
		token->token_str = new_str;
	}
	else
	{
		free(token->token_str);
		token->token_str = buff;
	}
	if (token->token_type == HEREDOC_EXPANDABLE_FLAG
		|| token->token_type == HEREDOC_NON_EXPANDABLE_FLAG)
		token->token_type = TOKEN_FLAG;
	if (token->token_str == NULL)
		return (ERR);
	return (OK);
}
