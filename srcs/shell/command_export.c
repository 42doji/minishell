/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:35:27 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 15:04:17 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	check_env_var(char *str, int *error)
{
	if (ft_isdigit(*str))
	{
		if (*error == 0)
			print_error(NULL, "error: export bad syntax\n", 1);
		return (0);
	}
	return (1);
}

static void	add_env_var(t_minishell *mini, char *str)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = ft_calloc(sizeof(char *), get_env_count(mini) + 2);
	while (mini->env[++i])
		new_env[i] = ft_strdup(mini->env[i]);
	new_env[i] = ft_strdup(str);
	free_array(mini->env);
	mini->env = new_env;
}

void	command_export(t_minishell *mini, char **input)
{
	int	tmp;

	g_exit_status = 0;
	if (input[1] == NULL)
	{
		sort_and_print(mini);
		return ;
	}
	while (*++input)
	{
		if (check_for_equal_sign(*input, &mini->error) == 0)
			continue ;
		if (*input && check_env_var(*input, &mini->error))
		{
			if (has_env_var(mini->env, *input) != -1)
			{
				tmp = has_env_var(mini->env, *input);
				free(mini->env[tmp]);
				mini->env[tmp] = ft_strdup(*input);
			}
			else
				add_env_var(mini, *input);
		}
	}
	update_env_path(mini);
}
