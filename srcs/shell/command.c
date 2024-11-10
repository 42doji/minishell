/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:32:36 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 15:02:05 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_builtin_command_type(char *command)
{
	if (!command)
		return (0);
	if (!ft_strcmp(command, "cd"))
		return (CD);
	if (!ft_strcmp(command, "env"))
		return (ENV);
	if (!ft_strcmp(command, "pwd"))
		return (PWD);
	if (!ft_strcmp(command, "echo"))
		return (ECHO);
	if (!ft_strcmp(command, "exit"))
		return (EXIT);
	if (!ft_strcmp(command, "unset"))
		return (UNSET);
	if (!ft_strcmp(command, "export"))
		return (EXPORT);
	return (0);
}

void	execute_builtin_command(t_minishell *mini, char **arguments)
{
	int	type;

	type = to_builtin_command_type(arguments[0]);
	if (type == CD)
		command_cd(mini, arguments);
	else if (type == ENV)
		command_env(mini->env, arguments);
	else if (type == PWD)
		command_pwd();
	else if (type == ECHO)
		command_echo(arguments);
	else if (type == EXIT)
		command_exit(mini, arguments);
	else if (type == UNSET)
		command_unset(mini, arguments);
	else if (type == EXPORT)
		command_export(mini, arguments);
}
