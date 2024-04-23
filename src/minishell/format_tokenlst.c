/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_tokenlst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:59:46 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/23 20:30:51 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"



int	format_tokenlst(t_blst **tokens_lst)
{
	merge_redirects(tokens_lst);
	// delete_quote(tokens_lst);
	//現在が空白で、prevかnextのどちらかが特殊文字であれば自身を削除
	return (1);
}
