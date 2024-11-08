/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:46:52 by junmin            #+#    #+#             */
/*   Updated: 2024/11/08 17:02:26 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_error_redirection(t_token *check)
{
	t_token	*cur;

	cur = check;
	while (cur)
	{
		if (cur->type == SMALLER || cur->type == GREATER
			|| cur->type == HERE_DOC || cur->type == APPEND)
		{
			if (!cur->next || cur->next->type != STRING)
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

static int	has_error_pipe(t_token *check)
{
	t_token	*cur;

	cur = check;
	while (cur)
	{
		if (cur->type == PIPE)
		{
			if (!cur->prev || cur->prev->type == PIPE)
				return (1);
			else if (!cur->next)
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

static int	has_error_special(t_token *check)
{
	t_token	*cur;

	cur = check;
	while (cur)
	{
		if (cur->type != STRING && cur->type != GREATER
			&& cur->type != APPEND && cur->type != SMALLER
			&& cur->type != HERE_DOC && cur->type != PIPE)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	has_syntax_error(t_token *check)
{
	if (has_error_special(check) == 1)
	{
		print_error(NULL, "minishell: syntax error\n", 2);
		return (1);
	}
	if (has_error_redirection(check) == 1)
	{
		print_error(NULL, "minishell: syntax error\n", 2);
		return (1);
	}
	if (has_error_pipe(check) == 1)
	{
		print_error(NULL, "minishell: syntax error\n", 2);
		return (1);
	}
	return (0);
}
