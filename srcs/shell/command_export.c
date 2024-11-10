/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:35:27 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 11:15:40 by junmin           ###   ########.fr       */
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

static void	add_env_var(char *str)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = ft_calloc(sizeof(char *), get_env_count() + 2);
	while (g_minishell.env[++i])
		new_env[i] = ft_strdup(g_minishell.env[i]);
	new_env[i] = ft_strdup(str);
	free_array(g_minishell.env);
	g_minishell.env = new_env;
}

void	command_export(char **input)
{
	int	tmp;

	g_exit_status = 0;
	if (input[1] == NULL)
	{
		sort_and_print();
		return ;
	}
	while (*++input)
	{
		if (check_for_equal_sign(*input, &g_minishell.error) == 0)
			continue ;
		if (*input && check_env_var(*input, &g_minishell.error))
		{
			if (has_env(*input) != -1)
			{
				tmp = has_env(*input);
				free(g_minishell.env[tmp]);
				g_minishell.env[tmp] = ft_strdup(*input);
			}
			else
				add_env_var(*input);
		}
	}
	update_env_path();
}
