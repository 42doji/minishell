/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:35:48 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 14:34:57 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(t_minishell *mini, char *data)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(sizeof(char *), get_env_count(mini) + 1);
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], data, ft_strlen(data)))
		{
			new_env[j] = ft_strdup(mini->env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = 0;
	free_array(mini->env);
	mini->env = new_env;
}

void	command_unset(t_minishell *mini, char **input)
{
	char	*data;

	input++;
	while (*input)
	{
		data = ft_strjoin_without_free(*input, "=");
		remove_env_var(mini, data);
		free(data);
		input++;
	}
	update_env_path(mini);
	g_exit_status = 0;
}
