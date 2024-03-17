/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_2way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:11:34 by syamasaw          #+#    #+#             */
/*   Updated: 2024/02/29 15:48:03 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_token	*lst_last(t_token *tokens)
{
	if (tokens == NULL)
		return (NULL);
	while (tokens->next != NULL)
		tokens = tokens->next;
	return (tokens);
}

t_token	*lst_new(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	return (new);
}

t_token	*lstadd_token(t_token *tokens, char *str, int type)
{
	t_token	*lst_last_addr;
	t_token	*data;

	lst_last_addr = NULL;
	data = NULL;
	data = lst_new();
	data->token_str = ft_strdup(str);
	data->token_type = type;
	data->next = NULL;
	data->prev = NULL;
	if (tokens != NULL)
	{
		lst_last_addr = lst_last(tokens);
		data->prev = lst_last_addr;
		lst_last_addr->next = data;
		return (tokens);
	}
	return (data);
}

void	put_lst(t_token *tokens)
{
	while (tokens != NULL)
	{
		printf("%s type: %d\n", tokens->token_str, tokens->token_type);
		tokens = tokens->next;
	}
}

void	del_lst(t_token *tokens)
{
	while (tokens->next != NULL)
	{
		tokens = tokens->next;
		free(tokens->prev->token_str);
		free(tokens->prev);
	}
	free(tokens->token_str);
	free(tokens);
}
