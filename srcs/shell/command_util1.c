/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:24:06 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 11:19:14 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_env(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (g_minishell.env[i])
	{
		j = 0;
		while (g_minishell.env[i][j] && str[j])
		{
			if (str[j] == '=' && g_minishell.env[i][j] == '=')
				return (i);
			if (str[j] != g_minishell.env[i][j])
				break ;
			j++;
		}
		i++;
	}
	return (-1);
}

static void	export_print_all(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_minishell.env[i] != NULL)
	{
		j = 0;
		printf("declare -x ");
		while (g_minishell.env[i][j] != '=' && g_minishell.env[i][0])
		{
			printf("%c", g_minishell.env[i][j]);
			j++;
		}
		printf("%c", g_minishell.env[i][j]);
		printf("\"");
		j++;
		while (g_minishell.env[i][j])
		{
			printf("%c", g_minishell.env[i][j]);
			j++;
		}
		printf("\"\n");
		i++;
	}
}

void	sort_and_print(void)
{
	sort_env_variables(g_minishell.env);
	export_print_all();
}

void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_env_variables(char **env)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	while (env[count] != NULL)
	{
		count++;
	}
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
				swap_strings(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}
