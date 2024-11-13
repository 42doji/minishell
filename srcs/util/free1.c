/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:45:38 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 15:53:23 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_command_content(t_command *cmd)
{
	int j;

	if (cmd->cmd)
		free(cmd->cmd);
	j = -1;
	if (cmd->args)
	{
		while (cmd->args[++j])
			free(cmd->args[j]);
		free(cmd->args);
	}
	if (cmd->in_file > 2)
		close(cmd->in_file);
	if (cmd->out_file > 2)
		close(cmd->out_file);
}

static void free_file_list(t_file *file)
{
	t_file *tmp;

	while (file != NULL)
	{
		tmp = file->next;
		if (file->name)
			free(file->name);
		free(file);
		file = tmp;
	}
}

static void free_parser(t_minishell *mini, t_command **parsed)
{
	int i;

	i = -1;
	while (parsed && parsed[++i])
	{
		free_command_content(parsed[i]);
		free_file_list(parsed[i]->file);
		free(parsed[i]);
	}
	free(parsed);
	mini->parsed = NULL;
}

static void free_lexer(t_minishell *mini, t_token *token)
{
	t_token *tmp;
	t_token *current;

	current = token;
	while (current)
	{
		tmp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = tmp;
	}
	mini->token = NULL;
}

static void free_minishell(t_minishell *mini)
{
	int i;

	i = 0;
	while (mini->input[i])
		free(mini->input[i++]);
	free(mini->input);
	mini->input = NULL;
}

void	free_open_pipe(int **pipe)
{
	int	i;

	i = 0;
	while (pipe[i])
	{
		free(pipe[i]);
		i++;
	}
	free(pipe);
}


static void free_core_components(t_minishell *mini)
{
	if (mini->fd)
		free_fd_list(mini);
	if (mini->parsed)
		free_parser(mini, mini->parsed);
	if (mini->token)
		free_lexer(mini, mini->token);
	if (mini->input)
		free_minishell(mini);
}


void free_all(t_minishell *mini)
{
	if (!mini)
		return;
	free_core_components(mini);
	if (mini->str)
	{
		free(mini->str);
		mini->str = NULL;
	}
	if (mini->paths || mini->env)
		free_path_and_env(mini);
	mini->n_tokens2 = 0;
}