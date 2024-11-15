/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:42:37 by junmin            #+#    #+#             */
/*   Updated: 2024/11/16 00:11:36 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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
		return (ft_itoa(g_exit_status));
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

static char	*check_string(t_minishell *mini, char *str, int *i)
{
	char	*new_str;

	if (str[*i] == '$')
	{
		(*i)++;
		return (handle_env_var(mini->env, str, i));
	}
	else if (str[*i] == '"')
		return (check_quote_double(mini->env, str, i));
	else if (str[*i] == '\'')
		return (check_quote_single(str, i));
	else
	{
		new_str = char_to_string(str[*i]);
		(*i)++;
		return (new_str);
	}
}

void	replace_env_var(t_minishell *mini, int i)
{
	char	*new_str;
	char	*temp;
	char	*check_str;
	int		j;

	if (i > 0
		&& ft_strcmp(mini->input[i - 1], "<<") == 0
		&& mini->input[i] != NULL)
		return ;
	j = 0;
	temp = ft_calloc(1, sizeof(char));
	while (mini->input[i][j])
	{
		check_str = check_string(mini, mini->input[i], &j);
		new_str = ft_strjoin(temp, check_str);
		free(check_str);
		free(temp);
		temp = new_str;
	}
	replace_string(&mini->input[i], &temp);
}
