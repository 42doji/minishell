/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:54:11 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 15:09:49 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	return_fd(t_minishell *mini)
{
	dup2(mini->out2, STDOUT_FILENO);
	close(mini->out2);
	dup2(mini->in2, STDIN_FILENO);
	close(mini->in2);
}

void	execute_command(t_minishell *mini, t_command *temp, t_file *file)
{
	if (file == NULL)
	{
		execve_or_builtin(mini, temp->args);
		if (mini->pipe_flag == 0)
			return_fd(mini);
		else
			dup2(temp->in_file, STDIN_FILENO);
		return ;
	}
	while (file != NULL)
	{
		if (file->type == GREATER)
			redirect_in(mini, temp, &file);
		else if (file->type == SMALLER)
			redirect_out(mini, temp, &file);
		else if (file->type == APPEND)
			append(mini, temp, &file);
		else if (file->type == HERE_DOC)
			here_doc(mini, temp, &file, &(mini->fd));
		if (file == NULL && temp->next == NULL)
			return_fd(mini);
	}
}

void	execve_or_builtin(t_minishell *mini, char **args)
{
	int	pid;
	int	status;

	status = to_builtin_command_type(args[0]);
	if (mini->n_tokens2 == 1 && status != 0)
	{
		execute_builtin_command(mini, args);
		return ;
	}
	signal(SIGINT, sigint_handler);
	pid = fork();
	if (pid == 0)
	{
		if (status != 0)
		{
			execute_builtin_command(mini, args);
			exit(g_exit_status);
		}
		else
			execute_execve(mini, args);
	}
	return ;
}

static void	check_command(t_minishell *mini)
{
	int			status;
	t_command	**parsed;

	parsed = mini->parsed;
	status = to_builtin_command_type(parsed[0]->args[0]);
	mini->pipe_flag = 0;
	if (parsed[1] != NULL)
	{
		mini->pipe_flag = 1;
		pipe_handling(mini, parsed);
	}
	else
		execute_command(mini, parsed[0], parsed[0]->file);
	while (waitpid(0, &g_exit_status, 0) > 0)
		continue ;
	if (status == 0)
	{
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		else
			g_exit_status = 130;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
}

void	execution(t_minishell *mini)
{
	if (ft_strlen(mini->str) == 0)
		return ;
	dup_fds(mini);
	check_command(mini);
}
