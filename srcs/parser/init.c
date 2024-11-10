/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:43:27 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 11:17:55 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_new_array(char **temp)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	while (temp[i])
		i++;
	new = malloc((i + 1) * sizeof(char *));
	while (temp[j])
	{
		new[j] = ft_strdup(temp[j]);
		j++;
	}
	new[j] = NULL;
	g_minishell.str2 = new;
}

void	initialize_shell(char *str)
{
	char	**temp;
	t_token	*token;

	g_minishell.flag2 = 0;
	g_minishell.error = 0;
	add_history(str);
	lexer(str);
	temp = g_minishell.input;
	if (check_unfinished_quote(temp) == 1)
		return ;
	create_new_array(temp);
	search_env_var(temp);
	tokenizer(temp);
	token = g_minishell.token;
	if (has_syntax_error(token) == 1)
		return ;
	parse_command(0, 1, token);
	execution();
}
