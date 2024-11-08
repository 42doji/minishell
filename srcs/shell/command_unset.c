/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:35:48 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:46:48 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(char *data)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(sizeof(char *), get_env_count() + 1);
	while (g_minishell.env[i])
	{
		if (ft_strncmp(g_minishell.env[i], data, ft_strlen(data)))
		{
			new_env[j] = ft_strdup(g_minishell.env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = 0;
	free_array(g_minishell.env);
	g_minishell.env = new_env;
}

void	command_unset(char **input)
{
	char	*data;

	input++;
	while (*input)
	{
		data = ft_strjoin_without_free(*input, "=");
		remove_env_var(data);
		free(data);
		input++;
	}
	update_env_path();
	g_minishell.exit_status = 0;
}
