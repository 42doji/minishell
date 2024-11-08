/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <devoogie@icloud.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:34:40 by junmin            #+#    #+#             */
/*   Updated: 2024/03/03 00:24:39 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	index;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size > 0)
		dest_len = ft_strlen(dest);
	else
		dest_len = 0;
	if (size < dest_len + 1)
		return (src_len + size);
	index = 0;
	while (src[index] && index + dest_len + 1 < size)
	{
		dest[dest_len + index] = src[index];
		index++;
	}
	dest[dest_len + index] = 0;
	return (src_len + dest_len);
}
