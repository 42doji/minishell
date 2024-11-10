/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:42:53 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 16:19:29 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*try_get_env_var(char **env, char *var_name)
{
	int		i;
	int		j;
	char	*env_str;

	i = -1;
	j = 0;
	env_str = ft_strjoin_without_free(var_name, "=");
	while (env[++i])
	{
		if (!ft_strncmp(env[i], env_str, ft_strlen(env_str)))
		{
			while (env[i][j] != '=')
				j++;
			free(env_str);
			return (ft_strdup(&env[i][j + 1]));
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

int	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
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
