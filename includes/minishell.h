#ifndef MINISHELL_MINISHELL_H
# define MINISHELL_MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef enum e_error
{
	NO_ERROR,
	MALLOC_ERROR,
	OPEN_ERROR,
	CLOSE_ERROR,
	READ_ERROR,
	WRITE_ERROR,
	PIPE_ERROR,
	FORK_ERROR,
	EXECVE_ERROR,
	WAIT_ERROR,
	REDIRECTION_ERROR,
	ARGUMENT_ERROR,
	ENV_ERROR,
	EXIT_ERROR,
}	t_error;

typedef struct	s_env_var
{
	struct s_env_var	*next;
	char				*key;
	char				*value;
}	t_env_var;

void init(char *line);
void clean_words(char **words);
char **prompt(char *line);
char **ft_split_delim(char *line, char *delimeters);

void	ft_putstr_fd(char *str, int fd);
void	error_handler(t_error error);
size_t	is_quote(char c);
size_t	has_quote(char *line);
size_t	is_complete_quote(char *line, char quote);
size_t	is_backslash(char c);
size_t	is_semicolon(char c);
size_t	has_back_or_semicolon(char *line);
size_t	ft_strlen(char *str);
size_t	ft_strchrs(char *delimiters, char character);
size_t	count_tokens(char *line, char *delimeters);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
size_t	ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strchr(char *str, char c);
char	*ft_strstr(const char *haystack, const char *needle);
size_t ft_strncpy(char *dst, char *src, size_t n);
size_t ft_strcpy(char *dst, char *src);

char	*ft_strdup(const char *s);



/* env_utils.c */
t_env_var	*init_env(char **envp);
char		*get_env_value(t_env_var *env, const char *key);
void		set_env_value(t_env_var **env, const char *key, const char *value);
void		free_env(t_env_var *env);
void		delete_env_var(t_env_var **env, const char *key);
void		append_env_var(t_env_var **env, const char *key, const char *value);
void		replace_env_var(t_env_var **env, const char *key, const char *value);
void		print_env_var(t_env_var *env, const char *key);
void		print_env(t_env_var *env);


/* bulitins.c */
void echo(char **comm);
void print_history(void);

/* builtin_exit_status.c */
int		last_exit_status;
void	update_last_exit_status(int status);
char	*expand_exit_status(char *command);

/* pwd.c */
void pwd(void);

/* signal_handler.c */
void handle_sigint(int sig);
void handle_sigquit(int sig);
void handle_eof(void);
void init_signal_handlers(void);

/* libft */
int ft_strcmp(const char *s1, const char *s2);

#endif