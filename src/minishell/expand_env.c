/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:58:13 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/26 21:21:27 by syamasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "dbllst.h"

static void	*find_val(t_blst **tokens_lst, t_blst *env_lst);
static char	*get_non_val(char *str, char *tokenstr, int created, int i);
static char	*get_env_val(char *tokenstr, int i, int len, t_blst *env_lst);
static char	*get_env_for_key(char *search, t_blst *env_lst);
static char	*strjoin_with_free(char *str1, char *str2);
static int	get_val_len(char *str, int j);

// 1. tokenlstからVALでありHEREDOCではないトークンを探す
void	expamd_val(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*data;

	data = (*tokens_lst)->data;
	while ((*tokens_lst)->data != NULL)
	{
		data = (*tokens_lst)->data;
		if ((data->token_type == VAL_FLAG \
			|| data->token_type == DOUBLE_QUOTE_VAL_FLAG) \
			&& (data->sub_type != HEREDOC_FLAG \
			|| data->sub_type != HEREDOC_QUOTE_FLAG))
			find_val(tokens_lst, env_lst);
		*tokens_lst = (*tokens_lst)->next;
	}
	while ((*tokens_lst)->prev->data != NULL)
		*tokens_lst = (*tokens_lst)->prev;
}
// "aaa$PATH bbb$PATH"
// created 0, 3, 8, 12, 17
// $のときのi 3, 12

static void	*find_val(t_blst **tokens_lst, t_blst *env_lst)
{
	t_token_data	*tokendata;
	int				i;
	int				created;
	int				len;
	char			*str;
	char			*val;

	tokendata = (*tokens_lst)->data;
	i = 0;
	created = 0;
	printf("loopstart\n");
	str = ft_calloc(1, 1);
	if (!str)
		return (NULL);
	while (tokendata->token_str[i] != '\0')
	{
		printf("s%s\n", tokendata->token_str);
		if (tokendata->token_str[i] == '$') //$があった
		{
			str = get_non_val(str, tokendata->token_str, created, i);
			if (!str)
				return (NULL);
			printf("1:%s\n", str);
			created += i;
			len = get_val_len(tokendata->token_str, i + 1);
			val = get_env_val(tokendata->token_str, i + 1, len, env_lst);
			if (!val)
			{
				free(str);
				return (NULL);
			}
			printf("2:%s\n", val);
			str = strjoin_with_free(str, val); // 文字列を結合
			if (!str)
			{
				free(val);
				return (NULL);
			}
			printf("3:%s\n", str);
			i += (1 + len); // indexを$+環境変数名分更新
			created += (1 + len);
		}
		else
			i++;
		if (tokendata->token_str[i] == '\0')
		{
			if (created < i) //作成済み文字列が終端まで達していない
			{
				str = get_non_val(str, tokendata->token_str, created, i);
				if (!str)
					return (NULL);
			}
		}
		printf("%d\n", i);
	}
	free(tokendata->token_str);
	tokendata->token_str = str;
	printf("loopfin\n");
	return (NULL);
}

static char	*get_non_val(char *str, char *tokenstr, int created, int i)
{
	char	*new;
	char	*ret;

	// createdからi文字を抽出
	new = ft_substr(tokenstr, created, i);
	if (!new)
		return (NULL);
	// 抽出文字をstrjoin
	ret = strjoin_with_free(str, new);
	if (!ret)
		return (NULL);
	return (ret);
}

static char	*get_env_val(char *tokenstr, int i, int len, t_blst *env_lst)
{
	char	*name;
	char	*ret;

	// 環境変数名を取得
	name = ft_substr(tokenstr, i + 1, len); //i=3+1から4文字
	if (!name)
		return (NULL);
	// nameをkeyにして置換する文字列をenv_lstから探す
	ret = get_env_for_key(name, env_lst);
	if (!ret)
	{
		free(name);
		return (NULL);
	}
	return (ret);
}

static char	*get_env_for_key(char *search, t_blst *env_lst)
{
	t_blst		*tmp;
	t_env_data	*data;
	char		*ret;

	tmp = env_lst;
	while (tmp->data != NULL)
	{
		data = tmp->data;
		if (strcmp(search, data->key) == 0)
		{
			ret = ft_strdup(data->val);
			if (ret == NULL)
				return (NULL);
			return (ret);
		}
		tmp = tmp->next;
	}
	ret = ft_calloc(1, 1);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

//str1, str2を結合してそれらをfree
static char	*strjoin_with_free(char *str1, char *str2)
{
	char	*str;

	str = ft_strjoin(str1, str2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str == NULL)
		return (NULL);
	return (str);
}

static int	get_val_len(char *str, int j)
{
	int	i = 0;

	while (str[i + j] != '\0' && str[i + j] != ' ' && str[i + j] != '$')
	{
		i++;
	}
	return (i);
}
