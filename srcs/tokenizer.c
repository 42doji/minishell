#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>


size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t ft_strchrs(char *delimiters, char character)
{
	size_t	i;
	size_t 	len;

	len = ft_strlen(delimiters);
	i = 0;
	while (i < len)
	{
		if (delimiters[i] == character)
			return (1);
		i++;
	}
	return (0);
}

size_t	count_tokens(char *line, char *delimeters)
{
	size_t	count;
	size_t	i;
	size_t	in_quote;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (in_quote == 0)
				in_quote = is_quote(line[i]);
			else if (in_quote == is_quote(line[i]))
				in_quote = 0;
			i++;
		}
		if (in_quote)
			i++;
		else
		{
			if (ft_strchrs(delimeters, line[i]))
				i++;
			else
			{
				count++;
				while (line[i] && !ft_strchrs(delimeters, line[i]))
					i++;
			}
		}
	}
	return (count + has_quote(line));
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

char	**allocate_words(char *line)
{
	char	**words;
	size_t	words_count;
	size_t	i;

	words_count = count_tokens(line, " \t\n");
	words = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (i < words_count)
	{
		words[i] = NULL;
		i++;
	}
	words[words_count] = NULL;
	return (words);
}

void	free_words(char **words, size_t idx)
{
	size_t	i;

	i = 0;
	while (i < idx)
	{
		free(words[i]);
		i++;
	}
	free(words);

}

char **ft_split_delim(char *line, char *delimeters)
{
	char	**words;
	size_t	current_idx;
	size_t	word_idx;
	size_t	start_idx;
	size_t	in_quote;

	words = allocate_words(line);
	if (!words)
		return (NULL);
	current_idx = 0;
	word_idx = 0;
	in_quote = 0;
	while (line[current_idx])
	{
		if (is_quote(line[current_idx]) && in_quote == 0)
		{
			in_quote = 1;
			start_idx = current_idx + 1;
			current_idx++;
			while (line[current_idx] && !is_quote(line[current_idx]))
				current_idx++;
			words[word_idx] = (char *)malloc(sizeof(char) * (current_idx - start_idx + 1));
			if (!words[word_idx])
				return (free_words(words, word_idx), NULL);
			ft_strlcpy(words[word_idx], line + start_idx, current_idx - start_idx + 1);
			word_idx++;
			in_quote = 0;
			current_idx++;
		}
		if (ft_strchrs(delimeters, line[current_idx]))
			current_idx++;
		else
		{
			start_idx = current_idx;
			while (line[current_idx] && !ft_strchrs(delimeters, line[current_idx]))
				current_idx++;
			words[word_idx] = (char *)malloc(sizeof(char) * (current_idx - start_idx + 1));
			if (!words[word_idx])
				return (free_words(words, word_idx), NULL);
			ft_strlcpy(words[word_idx], line + start_idx, current_idx - start_idx + 1);
			word_idx++;
		}
	}
	return (words);
}
