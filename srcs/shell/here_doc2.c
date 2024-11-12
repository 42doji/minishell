/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:10:44 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:46:48 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_char_to_string(char *temp, char c)
{
	char	*char_str;
	char	*new_str;

	char_str = char_to_string(c);
	new_str = ft_strjoin(temp, char_str);
	temp = ft_strdup(new_str);
	free(new_str);
	free(char_str);
	return (temp);
}

char    *search_expansion(char **env, char *str)
{
	char    *temp;
	char    *var;
	char    *result;
	int     i;

	if (!str)
		return (NULL);
	temp = ft_calloc(1, sizeof(char));
	if (!temp)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			i++;
			var = handle_env_var(env, str, &i);
			result = ft_strjoin(temp, var);
			free(temp);  // 기존 temp 해제
			free(var);   // var 해제
			temp = result;
			if (!temp)
				return (NULL);
		}
		else
		{
			result = add_char_to_string(temp, str[i]);
			free(temp);  // 기존 temp 해제
			temp = result;
			if (!temp)
				return (NULL);
		}
	}
	return (temp);
}
