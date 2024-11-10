/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:35:35 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 14:51:46 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_current_cwd(t_minishell *mini)
{
	mini->old_pwd = getcwd(NULL, 0);
}

static void	update_pwd(t_minishell *mini)
{
	char	*pwd;
	char	*tmp;
	int		i;

	pwd = getcwd(NULL, 0);
	if (has_env_var(mini->env, "PWD=") != -1)
	{
		i = has_env_var(mini->env, "PWD=");
		free(mini->env[i]);
		tmp = ft_strjoin_without_free("PWD=", pwd);
		mini->env[i] = ft_strdup(tmp);
		free(tmp);
	}
	if (has_env_var(mini->env, "OLDPWD=") != -1)
	{
		i = has_env_var(mini->env, "OLDPWD=");
		free(mini->env[i]);
		tmp = ft_strjoin_without_free("OLDPWD=", mini->old_pwd);
		mini->env[i] = ft_strdup(tmp);
		free(tmp);
	}
	free(mini->old_pwd);
	free(pwd);
}

static void	go_dir_home(t_minishell *mini)
{
	char	*path;

	path = try_get_env_var(mini->env, "HOME");
	get_current_cwd(mini);
	if (chdir(path) == 0)
		g_exit_status = 0;
	else
		print_error(NULL, "error: Home directory not found.\n", 1);
	free(path);
	update_pwd(mini);
}

void	command_cd(t_minishell *mini, char **input)
{
	if (input[1])
	{
		get_current_cwd(mini);
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
		g_exit_status = 0;
		update_pwd(mini);
	}
	else
		go_dir_home(mini);
}
