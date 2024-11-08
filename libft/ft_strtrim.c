/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:44:56 by junmin            #+#    #+#             */
/*   Updated: 2024/03/06 19:04:55 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(const char *str, const char *set)
{
	char	*result;
	size_t	start;
	size_t	end;

	if (!str || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	while (str[start] && ft_strchr(set, str[start]))
		start++;
	while (end > start && str[end - 1] && ft_strchr(set, str[end - 1]))
		end--;
	result = ft_substr(str, start, end - start);
	return (result);
}
