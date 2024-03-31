/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/31 14:04:41 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

static int	find_contd_tube(t_blst *node)
{
	t_token_data	*data;

	while (node->data != NULL)
	{
		data = node->data;
		if (data->token_type == TUBE_FLAG)
			return (1);
		else if (data->token_type == SPACE_FLAG)
			node = node->next;
		else
			break ;
	}
	if (node->data == NULL)
		return (1);
	return (0);
}

static int	find_contd_redirect(t_blst *node)
{
	t_token_data	*data;

	while (node->data != NULL)
	{
		data = node->data;
		if (TUBE_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
			return (1);
		else if (data->token_type == SPACE_FLAG)
			node = node->next;
		else
			break ;
	}
	if (node->data == NULL)
		return (1);
	return (0);
}

//SyntaxErrorCases
//case1. 先頭のtokenでtypeがTUBE
//case2. 現在typeがTUBEで次tokenのtypeがTUBE
//case3. 現在typeがリダイレクトのどれかで次typeがTUBE
//case4. 現在typeがリダイレクトのどれかで次typeもリダイレクト
//case5. 現在typeがリダイレクトまたはTUBEで、nextがNULL
//case6. 現在typeがOPEN_QUOTE
static int	cmp_syntax(void *d, void *n)
{
	t_token_data	*data;
	t_blst			*node;

	data = d;
	node = n;
	if (node->prev->data == NULL && data->token_type == TUBE_FLAG)
		return (printf("A\n"), 1);
	if ((t_token_data *)node->next->data != NULL)
	{
		if (data->token_type == TUBE_FLAG)
			if (find_contd_tube(node->next))
				return (printf("B\n"), 1);
		if (LESS_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
			if (find_contd_redirect(node->next))
				return (printf("C\n"), 1);
	}
	else
		if (TUBE_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
			return (printf("D\n"), 1);
	if (data->token_type == OPEN_QUOTE_FLAG)
		return (printf("E\n"), 1);
	return (0);
}

//syntax_ok=1
static int	syntax_checker(t_blst *lst, t_cmp_f cmp_f)
{
	t_blst	*ret_node;
	int		i;

	if (lst == NULL)
		return (0);
	i = 0;
	ret_node = lst;
	while (ret_node->data != NULL)
	{
		if (cmp_f(ret_node->data, ret_node))
			return (0);
		ret_node = ret_node->next;
		i ++;
	}
	return (1);
}

int	parser(t_blst **tokens_lst)
{
	printf("debug: parse start\n");
	if (!syntax_checker(*tokens_lst, cmp_syntax))
		return (0);
	printf("debug: parse OK\n");
	return (1);
}

//tokenリスト内を走査して、""空文字列要素を削除
//"hoge""huge$VAL"->hogehuge$VAL (blank(' ', '\t')を挟まずに)連続する文字列を結合
//クオートの削除
//<, >, <<, >> の後に来るtokenをdelimiter(デリミタ)やfileとする(token_typeの変更?)
//各リダイレクトを順に読み込み、最終的な入力や出力先を保持する。(ここでリダイレクトの処理をするか、exec部分で処理するかは未定)
//(リダイレクトリストを作成？)
//ヒアドキュメントの展開
//変数展開 ARG="ho hoge"; ec$ARG がありえる
//"|"区切りでコマンド列ごとに分割
//< infile | echo hoge のような、実行可能コマンドがない場合も考慮して実装する。