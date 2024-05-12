/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:15:28 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/12 06:52:37 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static char	*get_value_from_env(char *tokenstr, int now, t_blst *envlst);
static char	*get_env_for_key(char *val_name, t_blst *env_lst);

// concat not_env_part string and env_part string
char	*add_val_to_str(
			char *tokstr, char *buff, t_indexes *index, t_blst *envlst)
{
	char	*not_env_part;
	char	*env_part;
	char	*expanded;

	not_env_part = ft_substr(tokstr, index->old, index->now - index->old);
	if (!not_env_part)
		return (NULL);
	env_part = get_value_from_env(tokstr, index->now, envlst);
	if (!env_part)
	{
		free(not_env_part);
		return (NULL);
	}
	expanded = strjoin_allfree(not_env_part, env_part);
	return (strjoin_allfree(buff, expanded));
}

// get the env value key from the token string
// ex) $PWD -> PWD
static char	*get_value_from_env(char *tokenstr, int now, t_blst *envlst)
{
	int		val_len;
	char	*val_name;
	char	*ret;

	val_len = get_val_len(tokenstr, now + 1);
	val_name = ft_substr(tokenstr, now + 1, val_len);
	if (!val_name)
		return (NULL);
	ret = get_env_for_key(val_name, envlst);
	free(val_name);
	return (ret);
}

// get the length of the value
// ex) $PWD -> 3
int	get_val_len(char *str, int now)
{
	int	i;

	i = 0;
	while (str[i + now] != '\0' && str[i + now] != ' ' && str[i + now] != '$')
	{
		i++;
	}
	return (i);
}

// get the env value where `val_name == env_lst->u_data.e_data->key`
static char	*get_env_for_key(char *val_name, t_blst *env_lst)
{
	t_blst		*tmp;
	t_env_data	*data;
	char		*ret;

	tmp = env_lst;
	while (tmp->u_data.e_data != NULL)
	{
		data = tmp->u_data.e_data;
		if (ft_strcmp(val_name, data->key) == 0)
		{
			ret = ft_strdup(data->val);
			if (ret == NULL)
				return (NULL);
			return (ret);
		}
		tmp = tmp->next;
	}
	ret = ft_strdup("");
	if (ret == NULL)
		return (NULL);
	return (ret);
}

// join two strings and free each string: str1, str2
char	*strjoin_allfree(char *str1, char *str2)
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
