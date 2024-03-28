/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:28:52 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/28 16:07:28 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

static t_blst		*new_token_node(char **line);
static t_token_data	*new_token_data(char **line);

void	*new_tokenizer(char **line)
{
	char		*line_head;
	t_blst		*ret;
	t_blst		*new_node;

	line_head = *line;
	while (**line != '\0' && is_blank(**line))
		(*line) ++;
	ret = doub_lstnew(NULL);
	while (ret != NULL && **line != '\0')
	{
		new_node = new_token_node(line);
		if (new_node == NULL)
		{
			doub_lstdelall(&ret, free_token_data);
			return (NULL);
		}
		doub_lstappend(&ret, new_node);
	}
	*line = line_head;
	return ((void *)ret);
}

static t_blst	*new_token_node(char **line)
{
	t_blst			*node;
	t_token_data	*data;

	data = new_token_data(line);
	if (data == NULL)
		return (NULL);
	node = doub_lstnew((void *)data);
	if (node == NULL)
	{
		free_token_data(data);
		return (NULL);
	}
	return (node);
}

static t_token_data	*new_token_data(char **line)
{
	t_token_data	*data;
	char			*next_token_str;
	int				next_token_type;

	next_token_type = 0;
	data = (t_token_data *)malloc(sizeof(t_token_data));
	if (data == NULL)
		return (NULL);
	next_token_str = allocate_next_token(line, &next_token_type);
	if (next_token_str == NULL)
	{
		free(data);
		return (NULL);
	}
	data->token_str = next_token_str;
	data->token_type = next_token_type;
	return (data);
}

void	free_token_data(void *data)
{
	t_token_data	*token_data;

	token_data = (t_token_data *)data;
	if (token_data == NULL)
		return ;
	if (token_data->token_str != NULL)
		free(token_data->token_str);
	free(token_data);
}
