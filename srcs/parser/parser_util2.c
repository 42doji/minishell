/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:37:57 by junmin            #+#    #+#             */
/*   Updated: 2024/11/08 19:51:35 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_string(char **old_str, char **new_str)
{
	free(*old_str);
	*old_str = ft_strdup(*new_str);
	free(*new_str);
}

int	check_quote(int k, t_token *token)
{
	if (g_minishell.str2[k])
	{
		if (g_minishell.str2[k][0] == '"' || g_minishell.str2[k][0] == '\'')
		{
			token->type = STRING;
			return (1);
		}
	}
	return (0);
}

int	num_token(char **str)
{
	int	i;
	int	a;

	i = 1;
	a = 0;
	while (str[i])
	{
		if (str[i][0] == '|')
			a++;
		i++;
	}
	if (a == 0)
	{
		g_minishell.n_tokens2 = 1;
		return (1);
	}
	else
		g_minishell.n_tokens2 = a + 1;
	return (g_minishell.n_tokens2);
}
