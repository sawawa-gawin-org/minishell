/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 07:33:25 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/22 21:57:55 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static void	process_token_length(t_blst **tmp, t_token_data *data);
static void	replace_noquote(char *str, int len);

void	delete_quote(t_blst **tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;

	tmp = *tokens_lst;
	while (tmp->data != NULL)
	{
		data = tmp->data;
		process_token_length(&tmp, data);
		if (tmp != NULL)
			tmp = tmp->next;
	}
}

static void	process_token_length(t_blst **tmp, t_token_data *data)
{
	int		len;
	void	*purged;

	len = ft_strlen(data->token_str);
	if (len == 2)
	{
		if (DOUBLE_QUOTE_FLAG <= data->token_type
			&& data->token_type <= SINGLE_QUOTE_FLAG)
		{
			purged = doub_lstpurge((void **)tmp);
			doub_lstdelone(purged, free_token_data);
		}
	}
	else if (2 < len && data->token_str[0] == data->token_str[len - 1])
	{
		replace_noquote(data->token_str, len);
	}
}

static void	replace_noquote(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len - 2)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
}
