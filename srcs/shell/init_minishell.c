/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:26:56 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 11:12:50 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**dup_env_var(char **ev)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (ev[i])
		i++;
	env_copy = malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return (0);
	i = -1;
	while (ev[++i])
		env_copy[i] = ft_strdup(ev[i]);
	env_copy[i] = 0;
	return (env_copy);
}

void	create_minishell(char **ev)
{
	errno = 0;
	g_minishell.env = dup_env_var(ev);
	g_minishell.paths = ft_split(getenv("PATH"), ':');
	g_minishell.token = NULL;
	g_minishell.parsed = NULL;
	g_minishell.fd = NULL;
	g_minishell.error = 0;
}
