/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:51:04 by junmin            #+#    #+#             */
/*   Updated: 2024/03/03 21:22:03 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	char	*result;

	result = (char *)s;
	while (*result)
	{
		if ((char)c == *result)
			return (result);
		result++;
	}
	if (*result == c)
		return (result);
	return (NULL);
}
