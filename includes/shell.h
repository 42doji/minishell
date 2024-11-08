/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:40:06 by junmin            #+#    #+#             */
/*   Updated: 2024/11/08 19:40:09 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "structs.h"

void		create_minishell(char **env);
void		initialize_shell(char *str);
void		ctrl_c(int signal);
void		ctrl_d(char *str);

void		execute_command(t_command *temp, t_file *file, t_fd **fd);
void		execve_or_builtin(char **args);
void		execution(void);
void		execute_execve(char **args);
void		execute_builtin_command(char **arguments);
void		dup_fds(t_command *temp);
void		sigint_handler(int signum);
void		pipe_handling(t_command **temp, t_fd **fd);
int			to_builtin_command_type(char *command);
int			check_if_path(char *str);
char		*ft_strjoin_without_free(char const *s1, char const *s2);
char		*env_var(char *env, int i);
char		*get_shell_env(char **env, char *str);

int			check_next_node(t_file **file);
void		here_doc(t_command *temp, t_file **file, t_fd **fd);
void		check_for_next_node(t_command *temp, t_file **file);
void		here_doc_sigint(int sig);
void		igonre_signal(void);
char		*search_expansion(char **env, char *str);

void		redirect_in(t_command *temp, t_file **file);
void		redirect_out(t_command *temp, t_file **file);
void		append(t_command *temp, t_file **file);

void		here_doc_handler(t_command *temp, t_file **file, t_fd **fd);
void		command_cd(char **input);
void		command_echo(char **input);
void		command_env(char **input);
void		command_exit(char **input);
void		command_pwd(void);
void		command_unset(char **input);
void		command_export(char **input);
void		sort_env_variables(char **env);
void		sort_and_print(void);
int			check_for_equal_sign(char *str, int *error);
int			check_while_n(char **input, int *i, int *a);
int			has_env(char *str);

void		update_env_path(void);
void		print_error(char *arg, char *message, int exit_status);
int			get_env_count(void);
int			handle_error(int error_code, char *custom_message);
int			check_quote(int k, t_token *token);
char		*get_env(char *var_name);

void		free_all(char *str);
void		free_fd_list(t_fd *fd);
void		free_path_and_env(void);
void		free_open_pipe(int **pipe);
void		free_array(char **arr);
void		free_str_2(char **str);

char		*check_type(int type);

#endif