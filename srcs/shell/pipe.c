/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:06:43 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 16:29:06 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**open_pipes(int n_token)
{
	int	**pipe_fd;
	int	i;
	int	a;

	i = (n_token - 1);
	pipe_fd = ft_calloc(i + 1, sizeof(int *));
	a = -1;
	while (++a < i)
	{
		pipe_fd[a] = malloc(sizeof(int) * 2);
		pipe(pipe_fd[a]);
	}
	return (pipe_fd);
}

static void	write_to_pipe(t_minishell *m, t_command **c, int **pp_fd, int i)
{
	if (c[i + 1] == NULL)
	{
		dup2(m->out, STDOUT_FILENO);
		c[i]->out_file = m->out;
		execute_command(m, c[i], c[i]->file);
		close(m->out);
		close(pp_fd[i - 1][READ_END]);
		return ;
	}
	else
	{
		dup2(pp_fd[i][WRITE_END], STDOUT_FILENO);
		c[i]->out_file = pp_fd[i][WRITE_END];
		execute_command(m, c[i], c[i]->file);
		close(pp_fd[i][WRITE_END]);
	}
	if (i > 0)
		close(pp_fd[i - 1][READ_END]);
}

static void	connect_pipes(t_minishell *m, t_command **c, int **pp_fd, int i)
{
	(void)c;
	if (c[i] == NULL)
	{
		dup2(m->in, STDIN_FILENO);
		close(m->in);
		return ;
	}
	if (i > 0)
	{
		dup2(pp_fd[i - 1][READ_END], STDIN_FILENO);
		c[i]->in_file = pp_fd[i - 1][READ_END];
	}
}

void	pipe_handling(t_minishell *mini, t_command **temp)
{
	int	i;
	int	**pipe_fd;

	i = 0;
	pipe_fd = open_pipes(mini->n_tokens2);
	while (temp[i])
	{
		write_to_pipe(mini, temp, pipe_fd, i++);
		connect_pipes(mini, temp, pipe_fd, i);
	}
	free_open_pipe(pipe_fd);
}
