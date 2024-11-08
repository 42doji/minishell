/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:15:59 by junmin            #+#    #+#             */
/*   Updated: 2024/03/03 21:23:10 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *buf, int c, size_t count)
{
	unsigned char	*result;

	result = (unsigned char *)buf;
	while (count--)
	{
		if ((unsigned char)c == *result)
			return (result);
		result++;
	}
	return (NULL);
}
