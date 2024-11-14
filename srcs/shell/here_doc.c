/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:15:05 by doji              #+#    #+#             */
/*   Updated: 2024/11/14 21:45:16 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	write_here_doc(int pipe_fd, char *str)
{
	write(pipe_fd, str, ft_strlen(str));
	write(pipe_fd, "\n", 1);
}

static void	exec_here_doc(char **env, int pipe_fd, t_file **file, char *str)
{
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			print_error((*file)->name, ": Delimeter Not found\n", 0);
			free(str);
			break ;
		}
		if (ft_strcmp(str, (*file)->name) == 0)
		{
			free(str);
			break ;
		}
		str = search_expansion(env, str);
		if ((*file)->next == NULL || (*file)->next->type != HERE_DOC)
			write_here_doc(pipe_fd, str);
		free(str);
	}
}

static void	parent_run(t_minishell *mi, int p[2], t_command *cmd, t_file **f)
{
	close(p[1]);
	igonre_signal();
	while (waitpid(0, &g_exit_status, 0) > 0)
		continue ;
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	dup2(cmd->out_file, STDOUT_FILENO);
	dup2(p[0], STDIN_FILENO);
	close(p[0]);
	mi->fd = mi->fd->next;
	if ((*f)->next != NULL)
	{
		*f = (*f)->next;
		return ;
	}
	else
	{
		*f = (*f)->next;
		if (cmd->args[0])
			execve_or_builtin(mi, cmd->args);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
}

void	here_doc(t_minishell *m, t_command *cmd, t_file **file, t_fd **fd)
{
	int		pipe_fd[2];
	int		pid;
	char	**env;
	char	*str;

	str = NULL;
	dup2((*fd)->out, STDOUT_FILENO);
	dup2((*fd)->in, STDIN_FILENO);
	env = m->env;
	pipe(pipe_fd);
	signal(SIGINT, &here_doc_sigint);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		exec_here_doc(env, pipe_fd[1], file, str);
		close(pipe_fd[1]);
		exit(g_exit_status);
	}
	else
		parent_run(m, pipe_fd, cmd, file);
}
