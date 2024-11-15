/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:41:05 by junmin            #+#    #+#             */
/*   Updated: 2024/11/15 23:52:16 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "structs.h"

int			check_unfinished_quote(char **str);
int			skip_quote(char *str, int i);
void		replace_env_var(t_minishell *mini, int i);
void		replace_string(char **old_str, char **new_str);
void		lexer(t_minishell *mini);
char		*char_to_string(char c);
char		*check_quote_single(char *input, int *i);
char		*check_quote_double(char **env, char *input, int *i);
char		*handle_env_var(char **env, char *str, int *i);

int			is_ifs(char c);
int			check_redirect_in(char *str, t_token *token);
int			check_redirect_out(char *str, t_token *token);
int			check_pipe(char *str, t_token *token);
void		tokenizer(t_minishell *mini);

void		parse_command(t_minishell *mini, t_token *token);
void		get_next_token(t_token *command_table);
void		handle_paranthesis(t_token **tokens_list, t_command **command);
void		skip_to_matching_parenthesis(t_token **command_token_list);
void		handle_paranthesis(t_token **tokens_list, t_command **command);
void		add_command_to_list(t_command *cur, t_command **list);
int			count_and_or_tokens(t_token *command_token_list);
int			cal_input_token(t_minishell *mini);
int			has_syntax_error(t_token *my_tokens);
t_command	*create_command(int in_file, int out_file);

#endif