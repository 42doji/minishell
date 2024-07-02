#include "../includes/minishell.h"

size_t is_quote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

size_t has_quote(char *line)
{
	size_t i;
	size_t quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			if (quote == 0)
				quote = is_quote(line[i]);
			else if (quote == is_quote(line[i]))
				quote = 1;
		}
		i++;
	}
	return (quote);
}

size_t is_complete_quote(char *line, char quote)
{
	size_t i;
	size_t quote_count;

	i = 0;
	quote_count = 0;
	while (line[i])
	{
		if (line[i] == quote)
			quote_count++;
		i++;
	}
	return (quote_count % 2 == 0);
}
