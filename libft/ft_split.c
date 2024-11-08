/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:16:29 by junmin            #+#    #+#             */
/*   Updated: 2024/03/06 19:03:55 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_free_arr(void **result, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
		free(result[index++]);
	free(result);
	result = NULL;
}

static size_t	get_word_length(char *str, char c, size_t pivot)
{
	size_t	index;

	index = 0;
	while (str[pivot + index] && str[pivot + index] != c)
		index++;
	return (index);
}

static size_t	get_word_count(char *str, char c)
{
	size_t	result;
	size_t	count;
	size_t	len;

	count = 0;
	result = 0;
	while (str[count])
	{
		if (str[count] == c)
		{
			count++;
			continue ;
		}
		len = get_word_length(str, c, count);
		if (len > 0)
			result++;
		count += len;
	}
	return (result);
}

static int	try_fill_data(char **result, char *str, char c)
{
	size_t	len;
	size_t	index;
	size_t	count;

	count = 0;
	index = 0;
	while (str[count])
	{
		if (str[count++] == c)
			continue ;
		count--;
		len = get_word_length(str, c, count);
		if (len > 0)
		{
			result[index] = ft_substr(str, count, len);
			if (!result[index])
			{
				ft_free_arr((void **)result, index);
				return (0);
			}
			count += len;
			index++;
		}
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	size_t	word_count;
	char	**result;
	int		is_fill;

	if (s == NULL)
		return (NULL);
	word_count = get_word_count((char *)s, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[word_count] = 0;
	is_fill = try_fill_data(result, (char *)s, c);
	if (is_fill == 0)
		return (NULL);
	return (result);
}
