#include "../includes/minishell.h"

void clean_words(char **words)
{
	size_t	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

char **prompt(char *line)
{
	size_t	i;
	char	**words;

	i = -1;
	line = readline("Dojishell: ");
	if (!line)
		return (NULL);
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	words = ft_split_delim(line, " \t\n");
	if (!words)
		return (free(line), NULL);
	while (words[++i])
		printf("Word %zu: %s\n", i, words[i]);
	clean_words(words);
	return (words);
}