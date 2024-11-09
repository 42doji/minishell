/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:40:19 by junmin            #+#    #+#             */
/*   Updated: 2024/11/08 22:48:41 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define READ_END 0
# define WRITE_END 1

typedef enum e_token_type
{
	PIPE = 0,
	GREATER = 1,
	SMALLER = 2,
	APPEND = 3,
	HERE_DOC = 4,
	STRING = 5,
}	t_token_type;

typedef enum e_error
{
	FILE_NOT_FOUND = 1,
	SYNTAX_ERROR = 2,
	PERM_DENIED = 4,
	CMD_NOT_FOUND = 127,
	SYSTEM_ERR = -1,
	MEMORY_ERR = -2,
	DUP_ERR = -3,
	FORK_ERR = -4,
	PIPE_ERR = -5
}	t_error;

typedef enum e_builtin_cmd
{
	CD = 1,
	ENV,
	PWD,
	ECHO,
	EXIT,
	UNSET,
	EXPORT
}	t_builtin_cmd;

typedef struct s_fd
{
	int			out;
	int			in;
	struct s_fd	*next;
}	t_fd;

typedef struct s_token
{
	int					n_tokens;
	char				*value;
	int					index;
	enum e_token_type	type;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

typedef struct s_file
{
	enum e_token_type	type;
	char				*name;
	struct s_file		*next;
}	t_file;

typedef struct s_command
{
	int					exec;
	int					in_file;
	int					out_file;
	char				*cmd;
	char				**args;
	t_file				*file;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

typedef struct s_sig
{
	int	ctrl_c;
	int	ctrl_d;
}	t_sig;

typedef struct s_minishell
{
	int						error;
	int						ignore;
	int						in;
	int						in2;
	int						out;
	int						out2;
	int						n_tokens;
	int						n_tokens2;
	int						index;
	int						commands;
	int						flag;
	int						flag2;
	int						pipe_flag;
	int						exit_status;
	char					*old_pwd;
	char					*str;
	char					**env;
	char					**paths;
	char					**str2;
	char					**input;
	t_fd					*fd;
	t_token					*token;
	t_command				**parsed;
}	t_minishell;

extern t_minishell	g_minishell;

#endif