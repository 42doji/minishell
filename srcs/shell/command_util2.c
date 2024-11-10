/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:40:25 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 14:43:50 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_count(t_minishell *mini)
{
	int	i;

	i = -1;
	while (mini->env[++i])
		;
	return (i);
}

void	update_env_path(t_minishell *mini)
{
	char	*path;

	if (mini->paths)
		free_array(mini->paths);
	path = try_get_env_var(mini->env, "PATH");
	if (!(*path))
		mini->paths = 0;
	else
		mini->paths = ft_split(path, ':');
	free(path);
}

int is_valid_digit_count(char *arg)
{
    int len;
    
    len = 0;
    if (*arg == '+' || *arg == '-')
        arg++;
    while (*arg == '0')
        arg++;
    while (*arg >= '0' && *arg <= '9')
    {
        len++;
        arg++;
    }
    if (*arg != '\0' || len > 19)
        return (0);
    return (1);
}
