/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:57:22 by syamasaw          #+#    #+#             */
/*   Updated: 2024/03/30 14:20:35 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
// #include "minishell.h"
// #include "dbllst.h"

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

// int	new_parser(t_blst **tokens)
// {
// 	(void)tokens;
// 	if (!new_syntax_checker(*tokens))
// 		return (0);
// 	return (1);
// }

// int	parser(t_token **tokens, struct sigaction *sa)
// {
// 	(void)sa;
// 	if (!syntax_checker(*tokens))
// 		return (0);
	
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
// 	return (1);
// }

/*
typedef struct s_cmd_table
{
	char **cmd; (={"ls", "-lar", "/Desktop", NULL})
	struct s_list *redirects_in;
	struct s_list *redirects_out;//ここ2つのリストについて順に操作を行い、最終的に使用するfdを割り出す(その過程でheredocの入力やファイルの新規作成を行う。)
	bool is_builtin;
}	t_cmd_table;
*/
// <、>、>>はfdがわかる。<<は文章でありファイルではないので、openでfdを知ることはできない。
//そのため、heredoc処理の出力をwriteでfd指定でpipeを通してcmd1に渡す。

