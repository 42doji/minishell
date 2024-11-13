/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:42:37 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 15:22:59 by junmin           ###   ########.fr       */
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

char *process_string(t_minishell *mini, int i, int *j)
{
	char *temp;
	char *new_str;
	char *check_str;

	temp = ft_calloc(1, sizeof(char));
	if (!temp)
		return NULL;
	while (mini->input[i][*j])
	{
		check_str = check_string(mini, mini->input[i], j);
		if (!check_str)
		{
			free(temp);
			return NULL;
		}
		new_str = ft_strjoin(temp, check_str);
		free(temp);       // 기존 temp 메모리 해제
		free(check_str);   // 임시 문자열 해제
		if (!new_str)
			return NULL;
		temp = new_str;
	}
	return temp;
}

static void handle_heredoc(t_minishell *mini, int *i)
{
	if (*i > 0 && mini->input[*i] &&
		ft_strcmp(mini->input[*i - 1], "<<") == 0)
		(*i)++;
}

void replace_string(char **old_str, char **new_str)
{
	free(*old_str);              // 기존 문자열 해제
	*old_str = *new_str;          // 새로운 문자열 할당
	*new_str = NULL;               // new_str 포인터 초기화
}

void replace_env_var(t_minishell *mini)
{
	char *temp;
	int i;
	int j;

	i = 0;
	while (mini->input[i])
	{
		j = 0;
		temp = process_string(mini, i, &j);
		if (!temp)
			return;
		replace_string(&mini->input[i], &temp);
		i++;
		handle_heredoc(mini, &i);
	}
}




