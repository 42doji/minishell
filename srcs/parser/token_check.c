/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:01:01 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:52:38 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	check_pipe(char *str, t_token *token)
{
	if (ft_strchr(str, '|') != 0)
	{
		token->type = PIPE;
		return (1);
	}
	else
		return (0);
}

static int	get_count_redirect(const char *s, char c)
{
	if (s[0] == c)
	{
		if (s[1] == c)
			return (2);
		return (1);
	}
	return (0);
}

int	check_redirect_in(char *str, t_token *token)
{
	if (get_count_redirect(str, '>') == 2)
	{
		token->type = APPEND;
		return (1);
	}
	else if (get_count_redirect(str, '>') == 1)
	{
		token->type = GREATER;
		return (1);
	}
	else
		return (0);
}

int	check_redirect_out(char *str, t_token *token)
{
	if (get_count_redirect(str, '<') == 2)
	{
		token->type = HERE_DOC;
		return (1);
	}
	else if (get_count_redirect(str, '<') == 1)
	{
		token->type = SMALLER;
		return (1);
	}
	else
		return (0);
}
