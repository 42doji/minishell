#include "../includes/minishell.h"

char *ft_strndup(const char *s, size_t n)
{
	char	*new_str;
	size_t	i;

	new_str = malloc(n + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

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
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			new_var = malloc(sizeof(t_env_var));
			new_var->key = ft_strndup(envp[i], equal_sign - envp[i]); //
			new_var->value = ft_strdup(equal_sign + 1);
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
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	current = malloc(sizeof(t_env_var));
	current->key = ft_strdup(key);
	current->value = ft_strdup(value);
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
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
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
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	append_env_var(env, key, value);
}

void cd_command(char **args, t_env_var **env)
{
	char *old_path;
	char *new_path;

	if (!args[1] || args[2])
	{
		printf("cd: wrong number of arguments\n");
		return ;
	}
	old_path = getcwd(NULL, 0);
	if (chdir(args[1]) == 0)
	{
		new_path = getcwd(NULL, 0);
		set_env_value(env, "OLDPWD", old_path);
		set_env_value(env, "PWD", new_path);
		free(old_path);
		free(new_path);
	}
	else
	{
		perror("cd");
		free(old_path);
	}
}
