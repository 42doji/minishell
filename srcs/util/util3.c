/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:09:10 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 14:10:44 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void dup_fds(t_minishell *mini)
{
	mini->in = -1;
	mini->in2 = -1;
	mini->out = -1;
	mini->out2 = -1;
	if (mini->parsed[0] && mini->parsed[0]->args[0])
	{
		mini->parsed[0]->in_file = dup(STDIN_FILENO);
		mini->parsed[0]->out_file = dup(STDOUT_FILENO);
	}
	mini->in = dup(STDIN_FILENO);
	mini->in2 = dup(STDIN_FILENO);
	mini->out = dup(STDOUT_FILENO);
	mini->out2 = dup(STDOUT_FILENO);
}

char    *get_shell_env(char **env, char *str)
{
	int    i;

	if (!env || !str)
		return (NULL);
	if (!*str)
		return (NULL);
	i = 0;
	while (env[i])
	{
		size_t env_len = ft_strlen(env[i]);
		size_t str_len = ft_strlen(str);
		if (env_len >= str_len)
		{
			if (ft_strncmp(env[i], str, str_len) == 0)
				return (env_var(env[i], str_len));
		}
		i++;
	}
	return (NULL);
}


int	check_if_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
