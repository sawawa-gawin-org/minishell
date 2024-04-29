/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:15:28 by syamasaw          #+#    #+#             */
/*   Updated: 2024/04/29 23:19:42 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_int.h"

static char	*get_value_from_env(char *tokenstr, int now, t_blst *envlst);
static char	*get_env_for_key(char *val_name, t_blst *env_lst);
static int	ft_strcmp(const char *s1, const char *s2);

char	*add_val_to_str(char *tokstr, char *str, int *now_old, t_blst *envlst)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;

	str1 = ft_substr(tokstr, now_old[1], now_old[0] - now_old[1]);
	if (!str1)
		return (NULL);
	str2 = get_value_from_env(tokstr, now_old[0], envlst);
	if (!str2)
	{
		free(str1);
		return (NULL);
	}
	str3 = strjoin_allfree(str1, str2);
	str4 = strjoin_allfree(str, str3);
	return (str4);
}

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

static char	*get_env_for_key(char *val_name, t_blst *env_lst)
{
	t_blst		*tmp;
	t_env_data	*data;
	char		*ret;

	tmp = env_lst;
	while (tmp->data != NULL)
	{
		data = tmp->data;
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

//str1, str2を結合してそれらをfree
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

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	u_c1;
	unsigned char	u_c2;

	i = 0;
	while (!(s1[i] == '\0' && s2[i] == '\0'))
	{
		u_c1 = (unsigned char) s1[i];
		u_c2 = (unsigned char) s2[i];
		if (u_c1 != u_c2)
			return ((int)(u_c1 - u_c2));
		i ++;
	}
	return (0);
}
