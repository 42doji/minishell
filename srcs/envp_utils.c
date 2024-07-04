#include "../includes/minishell.h"

t_env_var *init_env(char **envp)
{
	t_env_var	*head;
	t_env_var	*current;
	char		*equal_sign;
	t_env_var	*new_var;
	int	i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		equal_sign = strchr(envp[i], '=');
		if (equal_sign)
		{
			new_var = malloc(sizeof(t_env_var));
			new_var->key = strndup(envp[i], equal_sign - envp[i]); //
			new_var->value = strdup(equal_sign + 1);
			new_var->next = NULL;
			if (!head)
				head = new_var;
			else
				current->next = new_var;
			current = new_var;
		}
		i++;
	}
	return (head);
}

char	*get_env_value(t_env_var *env, const char *key)
{
	t_env_var *current;

	current = env;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	set_env_value(t_env_var **env, const char *key, const char *value)
{
	t_env_var *current;

	current = *env;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			return ;
		}
		current = current->next;
	}
	current = malloc(sizeof(t_env_var));
	current->key = strdup(key);
	current->value = strdup(value);
	current->next = *env;
	*env = current;
}

void free_env(t_env_var *env)
{
	t_env_var *current;
	t_env_var *next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void print_env(t_env_var *env)
{
	t_env_var *current;

	current = env;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void delete_env_var(t_env_var **env, const char *key)
{
	t_env_var *current;
	t_env_var *prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			printf("Deleting %s\n", key);
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void append_env_var(t_env_var **env, const char *key, const char *value)
{
	t_env_var *current;
	t_env_var *new_var;

	current = *env;
	new_var = malloc(sizeof(t_env_var));
	new_var->key = strdup(key);
	new_var->value = strdup(value);
	new_var->next = NULL;
	if (!current)
	{
		*env = new_var;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new_var;
}

void replace_env_var(t_env_var **env, const char *key, const char *value)
{
	t_env_var *current;

	current = *env;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			return ;
		}
		current = current->next;
	}
	append_env_var(env, key, value);
}
