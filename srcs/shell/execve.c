/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:35:27 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:46:57 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

void	execute(char *full_path, char **args)
{
	if (g_minishell.flag2 == 0)
	{
		execve(full_path, args, g_minishell.env);
		free_all(g_minishell.str);
		free_path_and_env();
		print_error(args[0], ": Permission denied\n", 126);
		exit(126);
	}
	else
	{
		free_all(g_minishell.str);
		free_path_and_env();
		exit(1);
	}
}

static char	*ft_strtok(char *str, char delimeter)
{
	int			i;
	static char	*old_str;
	char		*new_str;

	if (str != NULL)
		old_str = str;
	if (old_str == NULL)
		return (NULL);
	i = 0;
	while (1)
	{
		if (old_str[i] == delimeter)
		{
			new_str = ft_substr(old_str, 0, i);
			old_str = ft_strchr(old_str, delimeter) + 1;
			return (new_str);
		}
		else if (old_str[i] == '\0')
		{
			new_str = ft_substr(old_str, 0, i);
			old_str = NULL;
			return (new_str);
		}
		i++;
	}
}

static char	*search_path(char *arg, char *path)
{
	char	*total_path;
	char	*command;
	char	*tok;

	command = ft_strjoin_without_free("/", arg);
	tok = ft_strtok(path, ':');
	while (tok != NULL)
	{
		total_path = ft_strjoin(tok, command);
		if (access(total_path, F_OK) == 0)
		{
			free(command);
			return (total_path);
		}
		else
		{
			free(total_path);
			tok = ft_strtok(NULL, ':');
		}
	}
	free(command);
	print_error(arg, ": command not found\n", 127);
	free_all(g_minishell.str);
	free_path_and_env();
	return (NULL);
}

void	execute_execve(char **args)
{
	char	*total;
	char	*path;

	total = NULL;
	path = get_shell_env(g_minishell.env, "PATH");
	if (path == NULL)
	{
		print_error(args[0], ": No such file or directory\n", 127);
		exit(g_minishell.exit_status);
	}
	if (check_if_path(args[0]) == 0)
	{
		total = search_path(args[0], path);
		if (total == NULL)
		{
			free(path);
			exit(g_minishell.exit_status);
		}
		else
			execute(total, args);
		free(total);
	}
	else
		execute(args[0], args);
	free(path);
}
