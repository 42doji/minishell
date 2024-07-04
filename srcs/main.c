#include "../includes/minishell.h"





int main(int argc, char **argv, char **envp)
{
	t_env_var	*env;

	env = init_env(envp);

	(void)argc;
	(void)argv;
	(void)env;
	while (env->next)
	{
		printf("Key: %s\nValue: %s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}