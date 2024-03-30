/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:08:00 by syamasaw          #+#    #+#             */
/*   Updated: 2024/02/29 15:52:24 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

static int	is_blank_str(char *str);
static int	init_minishell(t_init_data *init_data);

int	minishell(char *envp[])
{
	char			*line;
	t_blst			*tokens_lst;
	t_blst			*shvals_lst;
	t_init_data		init_data;

	shvals_lst = get_env_all(envp); //既存の環境変数のリスト化
	if (shvals_lst == NULL)
		return (1);
	init_minishell(&init_data);
	line = NULL;
	while (1)
	{
		tokens_lst = NULL;
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (line[0] != '\0') //もし空白やタブなどの入力が行われている場合は履歴に残す。改行だけなら残さない。cmdの成否にかかわらず履歴に残る。
			add_history(line);
		if (is_blank_str(line))
		{
			free(line);
			continue ;
		}
		tokens_lst = new_tokenizer(&line);
		free(line);
		doub_lstdelall(&tokens_lst, free_token_data);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &init_data.save);
	doub_lstdelall(&shvals_lst, free_shval_data);
	return (0);
}

static int	init_minishell(t_init_data *init_data)
{
	tcgetattr(STDIN_FILENO, &init_data->save); //初期状態の取得
	init_data->term = init_data->save; //複製
	init_data->term.c_cflag &= ~(ECHOCTL); //制御文字を消す
	tcsetattr(STDIN_FILENO, TCSANOW, &init_data->term); //変更を即時反映
	set_signal(SIGINT, sig_handler, &init_data->sa);
	set_signal(SIGQUIT, SIG_IGN, &init_data->sa);
	return (0);
}

static int	is_blank_str(char *str)
{
	int	i;

	i = 0;
	while (is_blank(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	is_blank(int c)
{
	return (c == ' ' || c == '\t');
}
