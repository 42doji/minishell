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

static void	free_minishell(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->input[i])
	{
		free(mini->input[i]);
		i++;
	}
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

static void	free_parser(t_minishell *mini, t_command **parsed)
{
	t_file	*tmp;
	int		i;
	int		j;

	i = -1;
	while (parsed && parsed[++i])
	{
		j = -1;
		if (parsed[i]->cmd)
			free(parsed[i]->cmd);
		while (parsed[i]->args[++j])
			free(parsed[i]->args[j]);
		free(parsed[i]->args);
		tmp = parsed[i]->file;
		while (parsed[i]->file != NULL)
		{
			free(parsed[i]->file->name);
			tmp = parsed[i]->file->next;
			free(parsed[i]->file);
			parsed[i]->file = tmp;
		}
		free(parsed[i]);
	}
	free(parsed);
	mini->parsed = NULL;
}

static void	free_lexer(t_minishell *mini, t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	i = 0;
	while (i < mini->n_tokens)
	{
		free(token->value);
		tmp = token->next;
		free(token);
		token = tmp;
		i++;
	}
	mini->token = NULL;
}

void	free_all(t_minishell *mini)
{
	if (!mini)
		return ;
	if (mini->str)
	{
		free(mini->str);
		mini->str = NULL;
	}
	if (mini->input)
		free_minishell(mini);
	if (mini->token)
		free_lexer(mini, mini->token);
	if (mini->fd)
		free_fd_list(mini);
	if (mini->parsed)
		free_parser(mini, mini->parsed);
	mini->n_tokens2 = 0;
}
