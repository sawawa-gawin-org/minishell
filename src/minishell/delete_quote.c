/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-07 07:33:25 by syamasaw          #+#    #+#             */
/*   Updated: 2024-04-07 07:33:25 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static void	replace_noquote(char *str, int len);

void	delete_quote(t_blst **tokens_lst)
{
	t_blst			*tmp;
	t_token_data	*data;
	int				len;

	tmp = *tokens_lst;
	while (tmp->data != NULL)
	{
		len = 0;
		data = tmp->data;
		len = ft_strlen(data->token_str);
		if (len == 2)
		{
			if (DOUBLE_QUOTE_FLAG <= data->token_type && data->token_type <= SINGLE_QUOTE_FLAG)
				doub_lstpurge(&tmp);
		}
		else if (2 < len && data->token_str[0] == data->token_str[len - 1])
		{
			replace_noquote(data->token_str, len);
		}
		tmp = tmp->next;
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
