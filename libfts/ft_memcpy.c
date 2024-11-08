/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <devoogie@icloud.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:23:44 by junmin            #+#    #+#             */
/*   Updated: 2024/03/02 23:27:33 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*cast_dest;
	unsigned char	*cast_src;

	if (dest == src)
		return (dest);
	cast_dest = (unsigned char *)dest;
	cast_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		cast_dest[i] = cast_src[i];
		i++;
	}
	return (dest);
}
