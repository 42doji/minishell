/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:42:37 by junmin            #+#    #+#             */
/*   Updated: 2024/11/08 22:39:15 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

char	*env_var(char *env, int index)
{
	char	*str;
	int		i;
	int		j;

	index++;
	i = index;
	j = 0;
	while (env[i])
	{
		j++;
		i++;
	}
	str = malloc((j + 1) * sizeof(char));
	j = 0;
	while (env[index])
	{
		str[j] = env[index];
		j++;
		index++;
	}
	str[j] = '\0';
	return (str);
}

static char	*check_exit_status(char *str, int *i)
{
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_minishell.exit_status));
	}
	else if (str[*i] == '\0')
	{
		*i = ft_strlen(str);
		return (ft_strdup("$"));
	}
	else
	{
		if (str[*i] == '"' || str[*i] == '\'' || str[*i] == ' ')
		{
			return (ft_strdup("$"));
		}
		else
		{
			while (ft_isalnum(str[*i]) == 1)
				(*i)++;
			return (ft_strdup(""));
		}
	}
}

char	*handle_env_var(char **env, char *str, int *i)
{
	char	*new_str;
	int		count;
	int		j;
	int		k;

	count = -1;
	while (env[++count])
	{
		k = *i;
		j = 0;
		while (str[k] == env[count][j])
		{
			if (ft_isalnum(str[k + 1]) == 0 && env[count][j + 1] == '=')
			{
				*i = k + 1;
				return (env_var(env[count], j + 1));
			}
			j++;
			k++;
		}
	}
	new_str = check_exit_status(str, i);
	return (new_str);
}

static char	*check_string(char *str, int *i)
{
	char	**env;
	char	*new_str;

	env = g_minishell.env;
	if (str[*i] == '$')
	{
		(*i)++;
		return (handle_env_var(env, str, i));
	}
	else if (str[*i] == '"')
		return (check_quote_double(env, str, i));
	else if (str[*i] == '\'')
		return (check_quote_single(str, i));
	else
	{
		new_str = char_to_string(str[*i]);
		(*i)++;
		return (new_str);
	}
}

void	search_env_var(char **str)
{
	char	*new_str;
	char	*temp;
	char	*check_str;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		temp = ft_calloc(1, sizeof(char));
		while (str[i][j])
		{
			check_str = check_string(str[i], &j);
			new_str = ft_strjoin(temp, check_str);
			free(temp);
			temp = new_str;
			free(check_str);
		}
		replace_string(&str[i], &temp);
		i++;
		if (ft_strcmp(str[i - 1], "<<") == 0 && str[i] != NULL)
			i++;
	}
	g_minishell.input = str;
}
