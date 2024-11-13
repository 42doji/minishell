/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:54:24 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 16:30:13 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_n_option(char **input, int *i, int *flag)
{
	int	j;

	if (input[*i] && input[*i][0] == ' ')
		return ;
	while (input[*i])
	{
		j = 0;
		if (ft_strncmp(input[*i], "-n", 2) == 0)
		{
			j = 1;
			while (input[*i][++j] == 'n')
				continue ;
			if (input[*i][j] != '\0')
				return ;
			*flag = 1;
			(*i)++;
		}
		else
			return ;
	}
}
void    command_echo(char **input)
{
	int    i;
	int    flag;

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
	g_exit_status = 0;
}