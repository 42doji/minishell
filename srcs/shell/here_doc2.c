/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:10:44 by doji              #+#    #+#             */
/*   Updated: 2024/11/14 21:31:28 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_char_to_string(char *temp, char c)
{
	char	*char_str;
	char	*new_str;

	char_str = char_to_string(c);
	new_str = ft_strjoin(temp, char_str);
	free(temp);
	free(char_str);
	return (new_str);
}

char	*search_expansion(char **env, char *str)
{
	char	*temp;
	char	*result;
	char	*var;
	int		i;

	result = ft_calloc(1, sizeof(char));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			i++;
			var = handle_env_var(env, str, &i);
			temp = result;
			result = ft_strjoin(temp, var);
			free(temp);
			free(var);
		}
		if (str[i] == '\0')
			break ;
		if (str[i] == '$')
			continue ;
		result = add_char_to_string(result, str[i]);
	}
	return (result);
}
