/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:42:53 by filipa            #+#    #+#             */
/*   Updated: 2024/11/08 19:46:57 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

char	*get_env(char *var_name)
{
	int		i;
	int		j;
	char	*env_str;

	i = -1;
	j = 0;
	env_str = ft_strjoin_without_free(var_name, "=");
	while (g_minishell.env[++i])
	{
		if (!ft_strncmp(g_minishell.env[i], env_str, ft_strlen(env_str)))
		{
			while (g_minishell.env[i][j] != '=')
				j++;
			free(env_str);
			return (ft_strdup(&g_minishell.env[i][j + 1]));
		}
	}
	free(env_str);
	return (ft_calloc(sizeof(char *), 1));
}

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

static int	has_string_char(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_for_equal_sign(char *str, int *error)
{
	int	i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
	{
		if (*error == 0)
			print_error(NULL, "error: export bad syntax\n", 1);
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (*error == 0)
				print_error(NULL, "error: export bad syntax\n", 1);
			return (0);
		}
		i++;
	}
	if (has_string_char(&str[i], '=') == 1)
		return (1);
	return (0);
}
