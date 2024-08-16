/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 02:43:28 by syamasaw          #+#    #+#             */
/*   Updated: 2024/08/16 08:34:33 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_int.h"
#include "dbllst.h"
#include "env.h"

static int	valid_option(char **cmd, int *options, char ***name_words);
static int	flag_parser(char *flag_str);

/**
 * Executes the built-in export command.
 *
 * This function takes an array of command arguments,
 *  a pointer to a linked list representing the environment variables,
 *  and a mode indicating the execution mode.
 * It performs the necessary operations to handle the export command,
 *  such as adding or modifying environment variables.
 *
 * @param cmd The array of command arguments.
 * @param envlst A pointer to the linked list representing the environment
 * variables.
 * @param mode if this function called in main process, mode is 0.
 * if this function called in child process, mode is 1.
 * @return The exit status of the command.
 */
int	builtin_export(char **cmd, t_blst **envlst, int mode)
{
	int		status;
	int		options;
	char	**name_words;

	status = valid_option(cmd, &options, &name_words);
	if (status > 0)
		return (status);
	if (!name_words[0])
		return (export_print(*envlst, mode));
	return (export_env(name_words, envlst, mode));
}

/**
 * @brief Validates the options and extracts the name words from the command.
 *
 * This function takes a command, options, and name_words as parameters and
 * validates the options. It also extracts the name words from the command
 * and stores them in the name_words array.
 *
 * @param cmd The command to validate options and extract name words from.
 * @param options A pointer to an integer to store the validated options.
 * However, this value is not used in this function.
 * @param name_words A pointer to a pointer to store
 * the extracted name words.
 *
 * @return Returns an integer indicating the success
 * or failure of the operation.
 */
static int	valid_option(char **cmd, int *options, char ***name_words)
{
	int		flag_value;

	*name_words = cmd + 1;
	while (**name_words != NULL
		&& ft_strncmp(**name_words, "-", 1) == 0)
	{
		if (ft_strcmp(**name_words, "--") == 0)
		{
			(*name_words)++;
			break ;
		}
		flag_value = flag_parser(**name_words);
		if (flag_value == ERR)
			return (MISUSE_OF_SHELL_BUILTINS);
		*options |= flag_value;
		(*name_words)++;
	}
	return (OK);
}

/**
 * @brief Parses the flag string.
 *
 * This function takes a flag string as input and parses it
 * to determine the appropriate flag value.
 *
 * @param flag_str The flag string to be parsed.
 * @return The parsed flag value.
 * @note The flag value is not be used.
 */
static int	flag_parser(char *flag_str)
{
	int		flag;

	flag_str ++;
	flag = 0;
	while (*flag_str)
	{
		if (*flag_str == 'n' || *flag_str == 'f'
			|| *flag_str == 'p')
			flag |= 1;
		else
		{
			export_option_err(*flag_str);
			return (ERR);
		}
		flag_str++;
	}
	return (flag);
}
