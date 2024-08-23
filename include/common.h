/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:51:56 by root              #+#    #+#             */
/*   Updated: 2024/08/17 15:46:55 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>
# include <unistd.h>

# include "libft.h"

# define MSG_PREFIX "minishell: "
# define IS_MAIN_PROCESS 0
# define IS_CHILD_PROCESS 1

enum	e_STATUS_CODE
{
	EXIT_CALLED = -3,
	UNDEFINED = -2,
	ERR = -1,
	OK = 0,
	GENERAL_ERR = 1,
	ERR_ALLOCATE_MEMORY = 1,
	MISUSE_OF_SHELL_BUILTINS = 2,
	CMD_CNT_EXECUTE = 126,
	CMD_NOT_FOUND = 127,
	ERR_SIGINT = 130,
};

typedef int		(*t_cmp_f)(void *, void *);

typedef enum e_tokens
{
	TOKEN_FLAG = 1,
	TUBE_FLAG = 1 << 1,
	LESS_FLAG = 1 << 2,
	GREAT_FLAG = 1 << 3,
	HEREDOC_FLAG = 1 << 4,
	APPEND_FLAG = 1 << 5,
	DOUBLE_QUOTE_FLAG = 1 << 6,
	DOUBLE_QUOTE_VAL_FLAG = 1 << 7,
	SINGLE_QUOTE_FLAG = 1 << 8,
	VAL_FLAG = 1 << 9,
	SPACE_FLAG = 1 << 10,
	OPEN_QUOTE_FLAG = 1 << 11,
	HEREDOC_QUOTE_FLAG = 1 << 12,
	COMMAND_FLAG = 1 << 13
}			t_tokens;

// # define META_FLAG (LESS_FLAG | GREAT_FLAG | TUBE_FLAG | 
// 					HEREDOC_FLAG | APPEND_FLAG)
// # define QUOTE_FLAG (OPEN_QUOTE_FLAG | SINGLE_QUOTE_FLAG | 
// 					DOUBLE_QUOTE_VAL_FLAG | DOUBLE_QUOTE_FLAG)
// # define WORD_FLAG (VAL_FLAG | TOKEN_FLAG)
// # define BLANK_FLAG (SPACE_FLAG)

# define META_FLAG 62
# define QUOTE_FLAG 2496
# define WORD_FLAG 513
# define BLANK_FLAG 1024

typedef struct s_token_data
{
	t_tokens	token_type;
	t_tokens	sub_type;
	char		*token_str;
}			t_token_data;

typedef struct s_env_data
{
	char	*key;
	char	*val;
	int		exported;
}			t_env_data;

typedef struct s_indexes
{
	int		now;
	int		old;
}			t_indexes;

typedef struct s_pipex
{
	int		pipe_in_fd;
	int		pipe_out_fd;
	int		file_in_fd;
	int		file_out_fd;
	pid_t	pids;
	void	*head_node;
	int		index;
}				t_pipex;

typedef struct s_node
{
	struct s_node	*prev;
	union
	{
		t_token_data	*token_data;
		t_env_data		*env_data;
		t_pipex			*pipe_data;
		char			*str;
	}	u_data;
	struct s_node	*next;
}			t_blst;

typedef t_blst	t_tokenlst;
typedef t_blst	t_pipelst;

// builtin command errs
int		cd_argc_err(void);
int		cd_home_not_set_err(void);
int		cd_option_err(char *cmd);
int		cd_move_err(char *path);
int		cd_cwd_error(void);

int		export_option_err(char flag_char);
int		export_identifier_err(char *str);

int		env_err(char *cmd);

int		pwd_err(char *str);

int		exit_numeric_err(char *str);
int		exit_argc_err(void);

int		unset_arg_err(void);

int		cmdnotfound_error(char *cmd);
int		cmdnotexecutable_error(char *cmd);

int		syntax_unexpected_error(char *token);
int		syntax_unclose_quote_error(void);
int		branching_syntax_err_by_flag(int flag);

int		is_a_directory_error(char *filepath);
int		permission_denied_error(char *filepath);
int		no_such_file_or_directory_error(char *filepath);

#endif