/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:43:27 by junmin            #+#    #+#             */
/*   Updated: 2024/11/15 23:55:28 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_token(char *str, int i)
{
	while (str[i] && !is_ifs(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = skip_quote(str, i);
			if (str[i] == '|' || str[i] == '<' || str[i] == '>')
				return (i);
		}
		else if (str[i] == '|')
			return (++i);
		else if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
			return (++i);
		}
		else if (str[i + 1] == '|')
			return (++i);
		else if (str[i + 1] == '<' || str[i + 1] == '>')
			return (++i);
		else
			i++;
	}
	return (i);
}

static int	calculate_token_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_ifs(str[i]))
			i++;
		if (str[i] && !is_ifs(str[i]))
		{
			i = count_token(str, i);
			count++;
		}
		if (str[i] == '\0')
			break ;
	}
	return (count);
}

void	initialize_shell(t_minishell *mini)
{
	t_token	*token;

	mini->flag2 = 0;
	mini->error = 0;
	mini->in = dup(STDIN_FILENO);
	mini->out = dup(STDOUT_FILENO);
	add_history(mini->str);
	mini->n_tokens = calculate_token_count(mini->str);
	if (mini->n_tokens == 0)
		return ;
	lexer(mini);
	if (check_unfinished_quote(mini->input) == 1)
		return ;
	tokenizer(mini);
	token = mini->token;
	if (has_syntax_error(token) == 1)
		return ;
	parse_command(mini, token);
	execution(mini);
}
