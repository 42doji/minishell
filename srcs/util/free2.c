/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:56:00 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:46:48 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd_list(t_fd *fd)
{
	t_command	**temp;
	t_file		*file;
	t_fd		*tmp;
	int			i;

	i = -1;
	g_minishell.fd = fd;
	temp = g_minishell.parsed;
	while (temp[++i])
	{
		file = temp[i]->file;
		while (file)
		{
			tmp = fd->next;
			free(fd);
			fd = tmp;
			file = file->next;
		}
	}
	free(fd);
	g_minishell.fd = NULL;
}

void	free_path_and_env(void)
{
	int	i;

	i = 0;
	if (g_minishell.paths)
	{
		while (g_minishell.paths[i])
		{
			free(g_minishell.paths[i]);
			i++;
		}
		free(g_minishell.paths);
	}
	g_minishell.paths = NULL;
	i = 0;
	if (g_minishell.env)
	{
		while (g_minishell.env[i])
		{
			free(g_minishell.env[i]);
			i++;
		}
		free(g_minishell.env);
	}
	g_minishell.env = NULL;
}

void	free_str_2(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
	g_minishell.str2 = NULL;
}
