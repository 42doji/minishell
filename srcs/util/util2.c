/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:51:04 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:47:38 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

char	*char_to_string(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_strjoin_without_free(char const *s1, char const *s2)
{
	int		i;
	int		a;
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	i = ft_strlen(s1);
	a = ft_strlen(s2);
	str = malloc((a + i) * sizeof(char) + 1);
	if (!str)
		return (0);
	i = 0;
	a = 0;
	while (s1[i])
		str[a++] = s1[i++];
	i = 0;
	while (s2[i])
		str[a++] = s2[i++];
	str[a] = '\0';
	return (str);
}

int	check_while_n(char **input, int *i, int *a)
{
	if (input[*i][++(*a)] == 'n')
	{
		while (input[*i][*a] == 'n')
			(*a)++;
		return (1);
	}
	else
		return (0);
}
