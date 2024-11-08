/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:35:54 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:46:48 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(0, 0);
	if (!current_dir)
		print_error(NULL, "error: no such file or directory.\n", 127);
	else
	{
		g_minishell.exit_status = 0;
		printf("%s\n", current_dir);
	}
	free(current_dir);
}
