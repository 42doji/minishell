/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:37:57 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 14:49:24 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"





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
