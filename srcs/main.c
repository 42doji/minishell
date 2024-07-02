#include "../includes/minishell.h"





int main(int argc, char **argv, char **envp)
{
	char **words;
	char *line;

	line = NULL;
	(void)argc;
	(void)argv;
	(void)envp;
	init(line);
	while (1)
	{
		words = prompt(line);
		if (!words)
			break;
	}
	return (0);
}