/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:46:48 by junmin            #+#    #+#             */
/*   Updated: 2024/11/08 16:52:43 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_odd_quote(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (str[*i] == c)
	{
		(*i)++;
		return (0);
	}
	else
	{
		print_error(NULL, "error: unifinished quote\n", 2);
		return (1);
	}
}

int	check_unfinished_quote(char **str)
{
	int	i;
	int	a;

	i = 0;
	while (str[i])
	{
		a = 0;
		while (str[i][a])
		{
			if (str[i][a] == '\'')
			{
				if (check_odd_quote(str[i], &a, '\'') == 1)
					return (1);
			}
			else if (str[i][a] == '"')
			{
				if (check_odd_quote(str[i], &a, '"') == 1)
					return (1);
			}
			else
				a++;
		}
		i++;
	}
	return (0);
}
