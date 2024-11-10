/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:36:29 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 11:12:48 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	igonre_signal(void)
{
	signal(SIGINT, SIG_IGN);
}

void	here_doc_sigint(int sig)
{
	(void)sig;
	printf("\n");
	g_minishell.exit_status = 130;
	free_all(g_minishell.str);
	free_path_and_env();
	exit(g_exit_status);
}

void	ctrl_c(int signal)
{
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 128 + signal;
}

void	ctrl_d(char *str)
{
	if (!str)
	{
		printf("exit\n");
		free_all(str);
		free_path_and_env();
		exit(g_exit_status);
	}
}

void	sigint_handler(int signum)
{
	printf("\n");
	g_exit_status = 128 + signum;
}
