/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:26:56 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 15:51:11 by junmin           ###   ########.fr       */
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

void create_minishell(t_minishell *mini, char **ev)
{
	errno = 0;
	mini->env = dup_env_var(ev);
	mini->paths = ft_split(getenv("PATH"), ':');
	mini->token = NULL;
	mini->parsed = NULL;
	mini->fd = NULL;
	mini->error = 0;
}
