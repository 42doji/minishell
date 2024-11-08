/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:40:25 by junmin            #+#    #+#             */
/*   Updated: 2024/11/08 18:43:26 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	get_env_count(void)
{
	int	i;

	i = -1;
	while (g_minishell.env[++i])
		;
	return (i);
}

void	update_env_path(void)
{
	char	*path;

	if (g_minishell.paths)
		free_array(g_minishell.paths);
	path = get_env("PATH");
	if (!(*path))
		g_minishell.paths = 0;
	else
		g_minishell.paths = ft_split(path, ':');
	free(path);
}
