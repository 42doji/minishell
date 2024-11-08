/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:57:33 by junmin            #+#    #+#             */
/*   Updated: 2024/03/06 18:56:10 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*new;
	int		len;

	new = malloc((ft_strlen((char *)src) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	len = 0;
	while (src[len])
	{
		new[len] = src[len];
		len++;
	}
	new[len] = 0;
	return (new);
}
