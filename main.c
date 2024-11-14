/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:00:53 by junmin            #+#    #+#             */
/*   Updated: 2024/11/14 20:19:05 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

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
	char		*str;
	t_minishell	mini;

	(void)argc;
	(void)argv;
	create_minishell(&mini, envp);
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline(PROMPT);
		mini.str = str;
		ctrl_d(&mini);
		if (check_if_empty(str) == 1)
		{
			if (mini.str)
				free(mini.str);
			mini.str = NULL;
			continue ;
		}
		initialize_shell(&mini);
		free_all(&mini);
	}
}
