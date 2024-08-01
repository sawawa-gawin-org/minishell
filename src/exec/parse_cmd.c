/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 07:27:21 by saraki            #+#    #+#             */
/*   Updated: 2024/08/01 18:17:56 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_int.h"

static int	count_tokenlst_section_size(
				t_tokenlst *section_start_node);

char	**parse_cmd(
			t_exec_parametors *param, t_tokenlst **head_node, t_pipex *pipe)
{
	char	**cmd;

	parse_redirects(head_node, pipe);
	cmd = convert_tokenlst_to_char_array(*head_node);
	if (cmd == NULL)
		return (NULL);
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
		size ++;
		now_node = now_node->next;
	}
	return (size);
}
