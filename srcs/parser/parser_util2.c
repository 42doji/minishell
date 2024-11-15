/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:37:57 by junmin            #+#    #+#             */
/*   Updated: 2024/11/16 00:10:36 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_string(char **old_str, char **new_str)
{
	free(*old_str);
	*old_str = ft_strdup(*new_str);
	free(*new_str);
}

char	*string_join_and_free(char *str1, char *str2)
{
	char	*joined;

	joined = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (joined);
}

int	check_quote(t_minishell *mini, int k, t_token *token)
{
	if (mini->input[k])
	{
		if (mini->input[k][0] == '"' || mini->input[k][0] == '\'')
		{
			token->type = STRING;
			return (1);
		}
	}
	return (0);
}

int	cal_input_token(t_minishell *mini)
{
	int	i;
	int	a;

	i = 1;
	a = 0;
	while (mini->input[i])
	{
		if (mini->input[i][0] == '|')
			a++;
		i++;
	}
	if (a == 0)
	{
		mini->n_tokens2 = 1;
		return (1);
	}
	else
		mini->n_tokens2 = a + 1;
	return (mini->n_tokens2);
}
