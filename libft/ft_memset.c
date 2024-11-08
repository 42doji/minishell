/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:08:01 by junmin            #+#    #+#             */
/*   Updated: 2024/02/29 15:13:36 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			len;
	unsigned char	*cast;

	cast = s;
	len = 0;
	while (len < n)
	{
		cast[len] = c;
		len++;
	}
	return (s);
}
