/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:09:10 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:46:57 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_fds(t_command *temp)
{
	if (temp->args[0])
	{
		temp->in_file = dup(g_minishell.in);
		temp->out_file = dup(g_minishell.out);
	}
	g_minishell.in = dup(STDIN_FILENO);
	g_minishell.in2 = dup(STDIN_FILENO);
	g_minishell.out = dup(STDOUT_FILENO);
	g_minishell.out2 = dup(STDOUT_FILENO);
}

char	*get_shell_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (env_var(env[i], ft_strlen(str)));
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
