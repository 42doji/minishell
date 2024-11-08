/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:42:29 by junmin            #+#    #+#             */
/*   Updated: 2024/03/03 21:19:47 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	count;
	char	*str;

	count = 0;
	str = (char *)haystack;
	if (!*needle)
		return (str);
	if (len == 0)
		return (NULL);
	while (str[count] && count < len)
	{
		index = 0;
		while (str[count + index] == needle[index] && count + index < len)
		{
			index++;
			if (needle[index] == 0)
				return (str + count);
		}
		count++;
	}
	return (0);
}
