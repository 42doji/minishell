#ifndef MINISHELL_MINISHELL_H
# define MINISHELL_MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

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


#endif