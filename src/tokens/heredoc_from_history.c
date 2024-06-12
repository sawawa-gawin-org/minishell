/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_from_history.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:42:09 by saraki            #+#    #+#             */
/*   Updated: 2024/06/12 11:46:07 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

char	*allocate_heredoc_string_from_history(
			char *delimiter, t_token_data *target_node)
{
	char	*history;
	char	*new_token_str;
	size_t	new_token_len;
	char	*last_input;

	last_input = target_node->token_str + ft_strlen(delimiter) + 1;
	new_token_len = ft_strlen(last_input) - (ft_strlen(delimiter) + 1);
	new_token_str = ft_substr(target_node->token_str,
			ft_strlen(delimiter) + 1, new_token_len);
	if (new_token_str == NULL)
		return (NULL);
	history = ft_strdup("");
	if (history == NULL)
	{
		free(new_token_str);
		return (NULL);
	}
	update_token_str_data(target_node, new_token_str);
	return (history);
}
