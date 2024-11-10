/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:40:06 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 15:51:44 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "structs.h"

void		create_minishell(t_minishell *mini, char **ev);
void		initialize_shell(t_minishell *mini);
void		ctrl_c(int signal);
void		ctrl_d(t_minishell *mini);

void		execute_command(t_minishell *mini, t_command *temp, t_file *file);
void		execve_or_builtin(t_minishell *mini, char **args);
void		execution(t_minishell *mini);
void		execute_execve(t_minishell *mini, char **args);
void		execute_builtin_command(t_minishell *mini, char **arguments);
void		dup_fds(t_minishell *mini);
void		sigint_handler(int signum);
void		pipe_handling(t_minishell *mini, t_command **temp);
int			to_builtin_command_type(char *command);
int			check_if_path(char *str);
char		*ft_strjoin_without_free(char const *s1, char const *s2);
char		*env_var(char *env, int i);
char		*get_shell_env(char **env, char *str);

int			check_next_node(t_file **file);
void		here_doc(t_minishell *mini, t_command *temp, t_file **file, t_fd **fd);
void		check_for_next_node(t_command *temp, t_file **file);
void		here_doc_sigint(int sig);
void		igonre_signal(void);
char		*search_expansion(char **env, char *str);

void		redirect_in(t_minishell *mini, t_command *temp, t_file **file);
void		redirect_out(t_minishell *mini, t_command *temp, t_file **file);
void		append(t_minishell *mini, t_command *temp, t_file **file);

void		here_doc_handler(t_command *temp, t_file **file, t_fd **fd);
void		command_cd(t_minishell *mini, char **input);
void		command_echo(char **input);
void		command_env(char **env, char **args);
void		command_exit(t_minishell *mini, char **input);
void		command_pwd(void);
void		command_unset(t_minishell *mini, char **input);
void		command_export(t_minishell *mini, char **input);
void		sort_env_variables(char **env);
void		sort_and_print(t_minishell *mini);
int			check_for_equal_sign(char *str, int *error);
int			check_while_n(char **input, int *i, int *a);
int			is_valid_digit_count(char *arg);

void		update_env_path(t_minishell *mini);
void		print_error(char *arg, char *message, int exit_status);
int			get_env_count(t_minishell *mini);
int			handle_error(int error_code, char *custom_message);
int			check_quote(t_minishell *mini, int k, t_token *token);
char		*try_get_env_var(char **env, char *var_name);
int			has_env_var(char **env,char *str);

void		free_all(t_minishell *mini);
void		free_fd_list(t_minishell *mini);
void		free_path_and_env(t_minishell *mini);

void		free_open_pipe(int **pipe);
void		free_array(char **arr);
char		*check_type(int type);

#endif