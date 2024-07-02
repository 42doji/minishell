#include "../includes/minishell.h"

size_t is_backslash(char c)
{
	if (c == '\\')
		return (1);
	return (0);
}

size_t is_semicolon(char c)
{
	if (c == ';')
		return (1);
	return (0);
}

size_t has_back_or_semicolon(char *line)
{
	size_t i;

	i = 0;
	while (line[i])
	{
		if (is_backslash(line[i]) || is_semicolon(line[i]))
			return (1);
		i++;
	}
	return (0);
}
