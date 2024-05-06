/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:30:24 by syamasaw          #+#    #+#             */
/*   Updated: 2024/05/01 15:36:56 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_int.h"

static char	*strjoin_with_free(char *s1, char *s2);
static char	*read_line(int fd, char *buf);
static char	*get_all_line(int fd);

char	*heredoc_open(char *delimiter)
{
	int		fd;
	char	*line;

	fd = heredoc_get(delimiter);
	if (fd == -1)
		return (NULL);
	line = get_all_line(fd);
	if (line == NULL)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (line);
}

// fdの文字列を終端まで読み込んでfree可能な文字列を返す
static char	*get_all_line(int fd)
{
	char	*buf;
	char	*ret;

	if ((read(fd, 0, 0) == -1) || fd < 0)
		return (NULL);
	buf = ft_calloc(1, 1);
	if (buf == NULL)
		return (NULL);
	ret = read_line(fd, buf);
	if (ret == NULL)
	{
		free(buf);
		return (NULL);
	}
	return (ret);
}

// strjoinでメモリ確保を行った後に前回実行時のメモリを解放する
static char	*strjoin_with_free(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	return (ret);
}

//fdの文字列を終端まで読み込む
static char	*read_line(int fd, char *buf)
{
	char	*tmp;
	ssize_t	read_byte;

	tmp = (char *)ft_calloc((100 + 1), sizeof(char));
	if (tmp == NULL)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0)
	{
		read_byte = read(fd, tmp, 100);
		if (read_byte == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[read_byte] = '\0';
		buf = strjoin_with_free(buf, tmp);
	}
	free(tmp);
	return (buf);
}
