/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:35:27 by doji              #+#    #+#             */
/*   Updated: 2024/11/16 00:41:26 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute(t_minishell *mini, char *full_path, char *path, char **args)
{
	if (mini->flag2 == 0)
	{
		execve(full_path, args, mini->env);
		print_error(args[0], ": Permission denied\n", 126);
		free_all(mini);
		free_path_and_env(mini);
		free(path);
		exit(126);
	}
	else
	{
		free_all(mini);
		free_path_and_env(mini);
		free(path);
		exit(1);
	}
}

static char	*ft_strtok(char *str, char delimeter)
{
	static char	*old_str;
	static char	*prev_str;
	char		*new_str;
	int			i;

	if (prev_str)
		free(prev_str);
	if (str != NULL)
		old_str = str;
	if (old_str == NULL)
		return (NULL);
	while (*old_str && *old_str == delimeter)
		old_str++;
	i = 0;
	while (old_str[i] && old_str[i] != delimeter)
		i++;
	new_str = ft_substr(old_str, 0, i);
	prev_str = new_str;
	if (old_str[i] != '\0')
		old_str = old_str + i + 1;
	else
		old_str = NULL;
	return (new_str);
}

static char	*search_path(t_minishell *mini, char *arg, char *path)
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
	free_all(mini);
	free_path_and_env(mini);
	return (NULL);
}

void	execute_execve(t_minishell *mini, char **args)
{
	char	*total;
	char	*path;

	total = NULL;
	path = get_shell_env(mini->env, "PATH");
	if (path == NULL)
	{
		print_error(args[0], ": No such file or directory\n", 127);
		exit(g_exit_status);
	}
	if (check_if_path(args[0]) == 0)
	{
		total = search_path(mini, args[0], path);
		if (total == NULL)
		{
			free(path);
			exit(g_exit_status);
		}
		else
			execute(mini, total, path, args);
	}
	else
		execute(mini, args[0], path, args);
}
