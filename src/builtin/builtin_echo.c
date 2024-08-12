/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:22:59 by saraki            #+#    #+#             */
/*   Updated: 2024/08/12 14:15:17 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "env.h"
#include "libft.h"

static int	valid_option(char **cmd, int *options, char ***put_strings);
static int	flag_parser(char *flag_str);

int	builtin_echo(char **cmd, t_blst **envlst, int mode)
{
	char	**put_strings;
	int		status;
	int		option;

	(void)envlst;
	if (mode == IS_MAIN_PROCESS)
		return (OK);
	option = 0;
	status = valid_option(cmd, &option, &put_strings);
	if (status > 0)
		return (status);
	while (*put_strings != NULL)
	{
		ft_putstr_fd(*put_strings, STDOUT_FILENO);
		if (*(put_strings + 1) != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		put_strings ++;
	}
	if (option == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (OK);
}

static int	valid_option(char **cmd, int *options, char ***put_strings)
{
	int		flag_value;

	*put_strings = cmd + 1;
	while (**put_strings != NULL
		&& ft_strncmp(**put_strings, "-", 1) == 0)
	{
		flag_value = flag_parser(**put_strings);
		if (flag_value == ERR)
			return (OK);
		*options |= flag_value;
		(*put_strings)++;
	}
	return (OK);
}

/**
 * @brief Parses the flags for the `builtin_echo` function.
 *
 * This function takes a string representing the flags
 * and parses them to determine the appropriate behavior
 * for the `builtin_echo` function.
 *
 * @param flag_str The string representing the flags.
 * @return An integer that the parsing succeeded or not.
 */
static int	flag_parser(char *flag_str)
{
	int		flag;

	flag_str ++;
	flag = 0;
	while (*flag_str)
	{
		if (*flag_str == 'n')
			flag |= 1;
		else
			return (ERR);
		flag_str++;
	}
	return (flag);
}
