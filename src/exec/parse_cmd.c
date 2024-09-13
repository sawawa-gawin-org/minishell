/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 07:27:21 by saraki            #+#    #+#             */
/*   Updated: 2024/09/13 07:17:32 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static int			count_tokenlst_section_size(
						t_tokenlst *section_start_node);
static t_tokenlst	*shift_token_section(
						t_tokenlst *token_head_node, int index);
static int			is_redirection(char *token);

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
	while (i < size && now_node->u_data.str != NULL)
	{
		if (is_redirection(now_node->u_data.str))
		{
			now_node = now_node->next->next;
			continue ;
		}
		cmd[i] = now_node->u_data.str;
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

	size = 0;
	now_node = head_node;
	while (now_node->u_data.str != NULL
		&& ft_strcmp(now_node->u_data.str, "|"))
	{
		if (is_redirection(now_node->u_data.str))
		{
			now_node = now_node->next->next;
			continue ;
		}
		size ++;
		now_node = now_node->next;
	}
	return (size);
}

static t_tokenlst	*shift_token_section(t_tokenlst *token_head_node, int index)
{
	int			i;
	t_tokenlst	*node;

	i = 0;
	node = token_head_node;
	while (i < index && node->u_data.str != NULL)
	{
		node = node->next;
		if (ft_strcmp(node->u_data.str, "|") == 0)
		{
			i++;
			node = node->next;
		}
	}
	return (node);
}

static int	is_redirection(char *token)
{
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
		|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
		return (1);
	return (0);
}
