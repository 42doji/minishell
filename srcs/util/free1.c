/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:45:38 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 11:12:47 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(void)
{
	int	i;

	i = 0;
	while (g_minishell.input[i])
	{
		free(g_minishell.input[i]);
		i++;
	}
	free(g_minishell.input);
	g_minishell.input = NULL;
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

static void	free_parser(t_command **parsed)
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
	g_minishell.parsed = NULL;
}

static void	free_lexer(t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	i = 0;
	while (i < g_minishell.n_tokens)
	{
		free(token->value);
		tmp = token->next;
		free(token);
		token = tmp;
		i++;
	}
	g_minishell.token = NULL;
}

void	free_all(char *str)
{
	if (str)
		free(str);
	if (g_minishell.input)
		free_minishell();
	if (g_minishell.token)
		free_lexer(g_minishell.token);
	if (g_minishell.fd)
		free_fd_list(g_minishell.fd);
	if (g_minishell.parsed)
		free_parser(g_minishell.parsed);
	if (g_minishell.str2)
		free_str_2(g_minishell.str2);
	g_minishell.n_tokens2 = 0;
}
