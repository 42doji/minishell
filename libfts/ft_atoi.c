/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <devoogie@icloud.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:54:37 by junmin            #+#    #+#             */
/*   Updated: 2024/03/03 01:18:56 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == 32)
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	char	*s;
	int		result;
	int		sign;

	result = 0;
	sign = 1;
	s = (char *)str;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && ft_isdigit(*s))
	{
		result = result * 10 + (*s - '0');
		s++;
	}
	return (result * sign);
}
