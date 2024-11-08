/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:35:35 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:49:21 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_current_cwd(void)
{
	g_minishell.old_pwd = getcwd(NULL, 0);
}

static void	update_pwd(void)
{
	char	*pwd;
	char	*tmp;
	int		i;

	pwd = getcwd(NULL, 0);
	if (has_env("PWD=") != -1)
	{
		i = has_env("PWD=");
		free(g_minishell.env[i]);
		tmp = ft_strjoin_without_free("PWD=", pwd);
		g_minishell.env[i] = ft_strdup(tmp);
		free(tmp);
	}
	if (has_env("OLDPWD=") != -1)
	{
		i = has_env("OLDPWD=");
		free(g_minishell.env[i]);
		tmp = ft_strjoin_without_free("OLDPWD=", g_minishell.old_pwd);
		g_minishell.env[i] = ft_strdup(tmp);
		free(tmp);
	}
	free(g_minishell.old_pwd);
	free(pwd);
}

static void	go_dir_home(void)
{
	char	*path;

	path = get_env("HOME");
	get_current_cwd();
	if (chdir(path) == 0)
		g_minishell.exit_status = 0;
	else
		print_error(NULL, "error: Home directory not found.\n", 1);
	free(path);
	update_pwd();
}

void	command_cd(char **input)
{
	if (input[1])
	{
		get_current_cwd();
		if (input[2])
		{
			print_error(NULL, "error: too many arguments.\n", 1);
			return ;
		}
		else if (chdir(input[1]))
		{
			print_error(NULL, "error: failed to change directory.\n", 1);
			return ;
		}
		g_minishell.exit_status = 0;
		update_pwd();
	}
	else
		go_dir_home();
}
