/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <devoogie@icloud.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:31:28 by junmin            #+#    #+#             */
/*   Updated: 2024/03/02 23:28:04 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dest == src)
		return (dest);
	if (dest <= src)
	{
		d = (unsigned char *)dest;
		s = (unsigned char *)src;
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d = (unsigned char *)dest + n;
		s = (unsigned char *)src + n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}
