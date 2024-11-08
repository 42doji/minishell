/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:00:53 by filipa            #+#    #+#             */
/*   Updated: 2024/11/08 19:46:57 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

int	check_if_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void)argc;
	(void)argv;
	create_minishell(envp);
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline(PROMPT);
		g_minishell.str = str;
		ctrl_d(str);
		if (check_if_empty(str) == 1)
			continue ;
		initialize_shell(str);
		free_all(str);
	}
}
