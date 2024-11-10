/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:43:34 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 16:27:00 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	save_token_special(char *str, int i)
{
	while (str[i] && !is_ifs(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = skip_quote(str, i);
			if (str[i] == '|' || str[i] == '<' || str[i] == '>')
				return (i - 1);
		}
		else if (str[i] == '|')
			return (i);
		else if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
			return (i);
		}
		else if (str[i + 1] == '|')
			return (i);
		else if (str[i + 1] == '<' || str[i + 1] == '>')
			return (i);
		else
			i++;
	}
	return (i - 1);
}

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

static void	save_token(t_minishell *mi)
{
	int	i;
	int	j;
	int	st;

	i = 0;
	while (mi->index < mi->n_tokens)
	{
		st = i;
		while (mi->str[i] && is_ifs(mi->str[i]))
			i++;
		j = i;
		if (mi->str[i] && !is_ifs(mi->str[i]))
		{
			i = save_token_special(mi->str, i);
			if (mi->index == 0 && st != j)
				mi->input[mi->index] = ft_substr(mi->str, st, (i - st) + 1);
			else
				mi->input[mi->index] = ft_substr(mi->str, j, (i - j) + 1);
		}
		if (mi->str[i] == '\0')
			break ;
		mi->index++;
		i++;
	}
}

void	lexer(t_minishell *mini)
{
	mini->n_tokens = calculate_token_count(mini->str);
	mini->input = malloc(sizeof(char *) * (mini->n_tokens + 1));
	if (!mini->input)
		exit(1);
	mini->input[mini->n_tokens] = NULL;
	mini->index = 0;
	save_token(mini);
}
