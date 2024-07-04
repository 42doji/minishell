#include "../includes/minishell.h"





int main(int argc, char **argv, char **envp)
{
	t_env_var	*env;

	env = init_env(envp);

	(void)argc;
	(void)argv;
	(void)env;
	char	*line[10] = {"echo","-n", "Hello", "World", NULL};
	char	*line2[10] = {"echo", "Hello", "World", NULL};

	printf("line2: ");
	echo(line2);
	printf("line1: ");
	echo(line);
	print_history();
	return (0);
}