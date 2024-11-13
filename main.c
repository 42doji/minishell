/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:00:53 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 16:03:46 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status;

void    cleanup_readline(void)
{
	rl_set_prompt("minishell$ ");
}

void    final_cleanup(void)
{
	clear_history();
	rl_clear_history();
	cleanup_readline();
}

int check_if_empty(char *str)
{
	int    i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	char          *str;
	t_minishell    mini;

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
		if (!check_if_empty(str))
		{
			add_history(str);
			initialize_shell(&mini);
		}
		cleanup_readline();
		free_all(&mini);
	}
	final_cleanup();
	return (0);
}