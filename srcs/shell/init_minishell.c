/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:26:56 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 16:31:32 by junmin           ###   ########.fr       */
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

void    create_minishell(t_minishell *mini, char **ev)
{
	// 전체 구조체를 0으로 초기화
	memset(mini, 0, sizeof(t_minishell));

	errno = 0;
	mini->env = dup_env_var(ev);

	char *path = getenv("PATH");
	if (path)
		mini->paths = ft_split(path, ':');

	// 명시적으로 NULL로 초기화
	mini->token = NULL;
	mini->parsed = NULL;
	mini->fd = NULL;
	mini->str = NULL;
	mini->input = NULL;  // 이 부분 추가
	mini->error = 0;
	mini->n_tokens2 = 0;
}