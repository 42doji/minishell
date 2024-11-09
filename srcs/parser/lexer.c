/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:43:34 by junmin            #+#    #+#             */
/*   Updated: 2024/11/08 16:19:31 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static int	save_token_special(char *str, int i)
{
	while (str[i] && str[i] != ' ')
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
	while (str[i] && str[i] != ' ')
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
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] != ' ')
		{
			i = count_token(str, i);
			count++;
		}
		if (str[i] == '\0')
			break ;
	}
	return (count);
}

static void	save_token(char *str)
{
	int	i;
	int	j;
	int start;

	i = 0;
	while (g_minishell.index < g_minishell.n_tokens)
	{
		start = i;
		while (str[i] && str[i] == ' ')
			i++;
		j = i;
		if (str[i] && str[i] != ' ')
		{
			i = save_token_special(str, i);
			if (g_minishell.index == 0 && start != j)
				g_minishell.input[g_minishell.index] = ft_substr(str, start, (i - start) + 1);
			else
				g_minishell.input[g_minishell.index] = ft_substr(str, j, (i - j) + 1);
		}
		
		if (str[i] == '\0')
			break ;
		g_minishell.index++;
		i++;
	}
}

void	lexer(char *str)
{
	g_minishell.n_tokens = calculate_token_count(str);
	g_minishell.input = malloc(sizeof(char *) * (g_minishell.n_tokens + 1));
	if (!g_minishell.input)
		exit(1);
	g_minishell.input[g_minishell.n_tokens] = NULL;
	g_minishell.index = 0;
	save_token(str);
}
