/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:56:00 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 14:02:37 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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

void free_path_and_env(t_minishell *mini)
{
	int i;

	free_paths(mini->paths);
	mini->paths = NULL;
	i = 0;
	if (mini->env)
	{
		while (mini->env[i])
			free(mini->env[i++]);
		free(mini->env);
	}
	mini->env = NULL;
}

