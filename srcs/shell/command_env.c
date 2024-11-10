/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:45:11 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 14:27:02 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_env(char **env, char **args)
{
	if (args[1])
	{
		print_error(args[1], "error: No such file or directory.\n", 127);
		return ;
	}
	else
		g_exit_status = 0;
	sort_env_variables(env);
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
