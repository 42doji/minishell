#include "minishell.h"

void	free_command_string(char **cmd_str)
{
	if (*cmd_str)
	{
		free(*cmd_str);
		*cmd_str = NULL;
	}
}

void	free_command_args(char ***args)
{
	int j = 0;

	if (*args)
	{
		while ((*args)[j])
		{
			free((*args)[j]);
			(*args)[j] = NULL;
			j++;
		}
		free(*args);
		*args = NULL;
	}
}

void close_command_files(int *in_file, int *out_file)
{
	if (*in_file > 2)
	{
		close(*in_file);
		*in_file = -1;
	}
	if (*out_file > 2)
	{
		close(*out_file);
		*out_file = -1;
	}
}

void free_file_list(t_file *file)
{
	t_file *current;
	t_file *next;

	current = file;
	while (current)
	{
		next = current->next;
		free_command_string(&current->name);
		free(current);
		current = next;
	}
}

void free_fd_list(t_minishell *mini)
{
	t_fd *current;
	t_fd *next;

	if (!mini || !mini->fd)
		return;
	current = mini->fd;
	while (current)
	{
		next = current->next;
		if (current->in >= 0)
			close(current->in);
		if (current->out >= 0)
			close(current->out);
		free(current);
		current = next;
	}
	mini->fd = NULL;
}

static void free_paths(char **paths)
{
	int i;

	i = 0;
	if (paths)
	{
		while (paths[i])
			free(paths[i++]);
		free(paths);
	}
}

void free_path(t_minishell *mini)
{
	free_paths(mini->paths);
	mini->paths = NULL;
}

void free_env(t_minishell *mini)
{
	int i;

	i = 0;
	if (mini->env)
	{
		while (mini->env[i])
			free(mini->env[i++]);
		free(mini->env);
	}
	mini->env = NULL;
}

void free_path_and_env(t_minishell *mini)
{
	free_path(mini);
	free_env(mini);
}

static void free_command_content(t_command *cmd)
{
	if (!cmd)
		return;
	free_command_string(&cmd->cmd);
	free_command_args(&cmd->args);
	free_file_list(cmd->file);
	cmd->file = NULL;
	close_command_files(&cmd->in_file, &cmd->out_file);
}

static void free_parser(t_minishell *mini)
{
	int i;

	if (!mini || !mini->parsed)
		return;
	for (i = 0; mini->parsed[i]; i++)
	{
		free_command_content(mini->parsed[i]);
		free(mini->parsed[i]);
		mini->parsed[i] = NULL;
	}
	free(mini->parsed);
	mini->parsed = NULL;
}

static void free_lexer(t_minishell *mini)
{
	t_token *current;
	t_token *next;

	if (!mini || !mini->token)
		return;
	current = mini->token;
	while (current)
	{
		next = current->next;
		free_command_string(&current->value);
		free(current);
		current = next;
	}
	mini->token = NULL;
}




void free_minishell_input(t_minishell *mini)
{
	int i;

	if (!mini->input)
		return;

	for (i = 0; mini->input[i]; i++)
	{
		free(mini->input[i]);
		mini->input[i] = NULL;
	}
	free(mini->input);
	mini->input = NULL;
}

void free_open_pipe(int **pipe)
{
	int i = 0;

	if (!pipe)
		return;

	while (pipe[i])
	{
		free(pipe[i]);
		pipe[i] = NULL;
		i++;
	}
	free(pipe);
	pipe = NULL;
}

void free_core_components(t_minishell *mini)
{
	if (mini->fd)
	{
		free_fd_list(mini);
		mini->fd = NULL;
	}
	free_parser(mini);
	free_lexer(mini);
	free_minishell_input(mini);
}

void free_all(t_minishell *mini)
{
	if (!mini)
		return;
	free_core_components(mini);
	free_path_and_env(mini);
}
