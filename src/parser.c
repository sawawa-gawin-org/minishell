/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/30 19:24:24 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dbllst.h"
#include "libft.h"
#include "minishell.h"

/*
Parser
1. read token list.
2. checks for syntax inconsistencies (e.g. ls > | echo, ls -l | | cat)
3. if inconsistencies are found, the flow comes to a halt and an error is returned.
*/

//空文字列""の削除、クオートの削除、文字列同士の結合

// int	syntax_checker(t_token *tokens)
// {
// 	while (tokens != NULL)
// 	{
// 		if (tokens->prev == NULL && tokens->token_type == 1)
// 			return (0);//先頭が|
// 		if (tokens->next != NULL)
// 		{
// 			if (tokens->token_type == 1 && tokens->next->token_type == 1)
// 				return (0);//| |
// 			if (less <= tokens->token_type && tokens->token_type <= append)
// 			{
// 				if (tokens->next->token_type == tube)
// 					return (0);//redirect |
// 				if (less <= tokens->next->token_type && tokens->next->token_type <= append)
// 					return (0);//redirect redirect
// 			}
// 		}
// 		else
// 			if (tube <= tokens->token_type && tokens->token_type <= append)
// 				return (0);//redirect EOF or | EOF
// 		if (tokens->token_type == open_quote)
// 			return (0);
// 		tokens = tokens->next;
// 	}
// 	return (1);
// }

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
	t_token_data	*next_data;
	t_blst			*node;

	data = d;
	node = n;
	next_data = node->next->data;
	if (node->prev->data == NULL && data->token_type == TUBE_FLAG)
		return (1);
	if (next_data != NULL)
	{
		if (data->token_type == TUBE_FLAG && next_data->token_type == TUBE_FLAG)
			return (1);
		if (LESS_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
		{
			if (TUBE_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
				return (1);
		}
	}
	else
		if (TUBE_FLAG <= data->token_type && data->token_type <= APPEND_FLAG)
			return (1);
	if (data->token_type == OPEN_QUOTE_FLAG)
		return (1);
	return (0);
}

//non-NULL=detect syntax_err
static t_blst	*syntax_checker(t_blst *lst, t_cmp_f cmp_f)
{
	t_blst	*ret_node;
	int		i;

	if (lst == NULL)
		return (NULL);
	i = 0;
	ret_node = lst;
	while (ret_node->data != NULL)
	{
		if (cmp_f(ret_node->data, ret_node))
			return (ret_node);
		ret_node = ret_node->next;
		i ++;
	}
	return (ret_node);
}

int	parser(t_blst **tokens_lst)
{
	(void)tokens_lst;
	printf("debug: parse start\n");
	if (syntax_checker(*tokens_lst, cmp_syntax) != NULL)
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