/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:40:06 by junmin            #+#    #+#             */
/*   Updated: 2024/03/09 17:59:23 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;
	int		check_size;

	check_size = count * size;
	if (count != 0 && check_size / count != size)
		return (NULL);
	result = malloc(count * size);
	if (!result)
		return (NULL);
	ft_memset(result, 0, count * size);
	return (result);
}
