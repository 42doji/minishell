/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:22:45 by junmin            #+#    #+#             */
/*   Updated: 2024/11/06 13:54:10 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, size_t start, size_t len)
{
	char	*result;
	size_t	index;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	result = ft_calloc((len + 1), sizeof(char));
	if (!result)
		return (0);
	index = 0;
	if (start >= s_len)
		return (result);
	while (s[start + index] && index < len)
	{
		result[index] = s[start + index];
		index++;
	}
	return (result);
}
