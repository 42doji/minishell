/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:54:24 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:46:48 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static void	check_n_option(char **input, int *i, int *flag)
{
	int	j;

	while (input[*i])
	{
		j = -1;
		if (input[*i][++j] == '-')
		{
			if (check_while_n(input, i, &j) == 0)
				return ;
			if (input[*i][j] != '\0')
				return ;
		}
		else
			return ;
		(*i)++;
		if (input[*i] && input[*i][0] != '-')
			break ;
		*flag = 1;
	}
	if (input[*i - 1][j] == '\0')
		*flag = 1;
}

void	command_echo(char **input)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (input[1] != NULL)
	{
		if (input[1][0] == '\0')
			i++;
		else
			check_n_option(input, &i, &flag);
	}
	while (input[i])
	{
		ft_putstr_fd(input[i], STDOUT_FILENO);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag == 0 || input[1] == NULL)
		write(STDOUT_FILENO, "\n", 1);
	g_minishell.exit_status = 0;
}
