/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:54:11 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 11:12:35 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	return_fd(void)
{
	dup2(g_minishell.out2, STDOUT_FILENO);
	close(g_minishell.out2);
	dup2(g_minishell.in2, STDIN_FILENO);
	close(g_minishell.in2);
}

void	execute_command(t_command *temp, t_file *file, t_fd **fd)
{
	if (file == NULL)
	{
		execve_or_builtin(temp->args);
		if (g_minishell.pipe_flag == 0)
			return_fd();
		else
			dup2(temp->in_file, STDIN_FILENO);
		return ;
	}
	while (file != NULL)
	{
		if (file->type == GREATER)
			redirect_in(temp, &file);
		else if (file->type == SMALLER)
			redirect_out(temp, &file);
		else if (file->type == APPEND)
			append(temp, &file);
		else if (file->type == HERE_DOC)
			here_doc(temp, &file, fd);
		if (file == NULL && temp->next == NULL)
			return_fd();
	}
}

void	execve_or_builtin(char **args)
{
	int	pid;
	int	status;

	status = to_builtin_command_type(args[0]);
	if (g_minishell.n_tokens2 == 1 && status != 0)
	{
		execute_builtin_command(args);
		return ;
	}
	signal(SIGINT, sigint_handler);
	pid = fork();
	if (pid == 0)
	{
		if (status != 0)
		{
			execute_builtin_command(args);
			exit(g_exit_status);
		}
		else
			execute_execve(args);
	}
	return ;
}

static void	check_command(t_command **temp, t_fd **fd)
{
	int	status;

	status = to_builtin_command_type(temp[0]->args[0]);
	g_minishell.pipe_flag = 0;
	if (temp[1] != NULL)
	{
		g_minishell.pipe_flag = 1;
		pipe_handling(temp, fd);
	}
	else
		execute_command(temp[0], temp[0]->file, fd);
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

void	execution(void)
{
	t_command	**temp;
	t_fd		*fd;

	temp = g_minishell.parsed;
	fd = g_minishell.fd;
	if (ft_strlen(g_minishell.str) == 0)
		return ;
	dup_fds(temp[0]);
	check_command(temp, &fd);
}
