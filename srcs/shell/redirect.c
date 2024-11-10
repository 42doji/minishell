/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:20:20 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 11:12:39 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append(t_command *command, t_file **file)
{
	int	file_fd;

	file_fd = open((*file)->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file_fd == -1)
	{
		print_error(NULL, "error: error opening file\n", 1);
	}
	if ((*file)->next == NULL || (*file)->next->type != APPEND)
	{
		dup2(file_fd, STDOUT_FILENO);
		if ((*file)->next != NULL)
		{
			*file = (*file)->next;
			close(file_fd);
			return ;
		}
		else if (command->args[0])
			execve_or_builtin(command->args);
	}
	close(file_fd);
	g_minishell.flag2 = 0;
	*file = (*file)->next;
}

void	redirect_out(t_command *command, t_file **file)
{
	int	file_fd;

	file_fd = open((*file)->name, O_RDONLY, 0644);
	if (file_fd == -1)
	{
		print_error((*file)->name, ": Not found\n", 1);
		g_minishell.flag2 = 1;
		*file = (*file)->next;
		return ;
	}
	if ((*file)->next == NULL || (*file)->next->type != SMALLER)
	{
		dup2(file_fd, STDIN_FILENO);
		if ((*file)->next != NULL)
		{
			*file = (*file)->next;
			close(file_fd);
			return ;
		}
		else if (command->args[0])
			execve_or_builtin(command->args);
	}
	close(file_fd);
	g_minishell.flag2 = 0;
	*file = (*file)->next;
}

void	redirect_in(t_command *command, t_file **file)
{
	int	file_fd;

	file_fd = open((*file)->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_fd == -1)
	{
		print_error(NULL, "error: error opening file\n", 1);
	}
	if ((*file)->next == NULL || (*file)->next->type != GREATER)
	{
		dup2(file_fd, STDOUT_FILENO);
		if ((*file)->next != NULL)
		{
			*file = (*file)->next;
			close(file_fd);
			return ;
		}
		else if (command->args[0])
			execve_or_builtin(command->args);
	}
	close(file_fd);
	g_minishell.flag2 = 0;
	*file = (*file)->next;
}
