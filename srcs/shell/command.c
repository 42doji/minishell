/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:32:36 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:46:48 by junmin           ###   ########.fr       */
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

void	execute_builtin_command(char **arguments)
{
	int	type;

	type = to_builtin_command_type(arguments[0]);
	if (type == CD)
		command_cd(arguments);
	else if (type == ENV)
		command_env(arguments);
	else if (type == PWD)
		command_pwd();
	else if (type == ECHO)
		command_echo(arguments);
	else if (type == EXIT)
		command_exit(arguments);
	else if (type == UNSET)
		command_unset(arguments);
	else if (type == EXPORT)
		command_export(arguments);
}
