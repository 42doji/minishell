/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:46:03 by junmin            #+#    #+#             */
/*   Updated: 2024/03/06 18:56:03 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	get_digit(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		digit;
	int		is_minor;
	char	*result;

	is_minor = n < 0;
	digit = get_digit(n);
	result = malloc((digit + 1 + is_minor) * sizeof(char));
	if (!result)
		return (0);
	if (is_minor)
		result[0] = '-';
	result[digit + is_minor] = 0;
	while (digit--)
	{
		result[digit + is_minor] = n % 10;
		if (is_minor)
			result[digit + is_minor] *= -1;
		result[digit + is_minor] += '0';
		n /= 10;
	}
	return (result);
}
