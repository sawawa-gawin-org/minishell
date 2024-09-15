/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 07:27:21 by saraki            #+#    #+#             */
/*   Updated: 2024/09/15 09:39:27 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static int			count_tokenlst_section_size(
						t_tokenlst *section_start_node);
static t_tokenlst	*shift_token_section(
						t_tokenlst *token_head_node, int index);

char	**parse_cmd(t_tokenlst *token_list, t_pipex *pipe, int *status)
{
	char		**cmd;
	t_tokenlst	*start_node;

	start_node = shift_token_section(token_list, pipe->index);
	if (parse_redirects(start_node, pipe) != OK)
	{
		*status = GENERAL_ERR;
		return (NULL);
	}
	cmd = convert_tokenlst_to_char_array(start_node);
	if (cmd == NULL)
	{
		*status = GENERAL_ERR;
		return (NULL);
	}
	return (cmd);
}

char	**convert_tokenlst_to_char_array(t_tokenlst *head_node)
{
	int			i;
	int			size;
	t_tokenlst	*now_node;
	char		**cmd;

	size = count_tokenlst_section_size(head_node);
	cmd = (char **)malloc(sizeof(char *) * (size + 1));
	if (cmd == NULL)
		return (NULL);
	i = 0;
	now_node = head_node;
	while (i < size && now_node->u_data.token_data != NULL)
	{
		if (now_node->u_data.token_data->token_type
			& (LESS_FLAG | GREAT_FLAG | HEREDOC_FLAG | APPEND_FLAG))
		{
			now_node = now_node->next->next;
			continue ;
		}
		cmd[i] = now_node->u_data.token_data->token_str;
		now_node = now_node->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

static int	count_tokenlst_section_size(t_tokenlst *head_node)
{
	t_tokenlst	*now_node;
	int			size;
	t_tokens	type;

	size = 0;
	now_node = head_node;
	while (now_node->u_data.token_data != NULL
		&& now_node->u_data.token_data->token_type != TUBE_FLAG)
	{
		type = now_node->u_data.token_data->token_type;
		if (type & (LESS_FLAG | GREAT_FLAG | HEREDOC_FLAG | APPEND_FLAG))
		{
			now_node = now_node->next->next;
			continue ;
		}
		size ++;
		now_node = now_node->next;
	}
	return (size);
}

static t_tokenlst	*shift_token_section(t_tokenlst *token_node, int index)
{
	int			i;

	i = 0;
	while (i < index && token_node->u_data.token_data != NULL)
	{
		token_node = token_node->next;
		if (token_node->u_data.token_data->token_type == TUBE_FLAG)
		{
			i++;
			token_node = token_node->next;
		}
	}
	return (token_node);
}
