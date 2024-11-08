/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:44:27 by junmin            #+#    #+#             */
/*   Updated: 2024/03/03 11:28:40 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	index;

	index = 0;
	if (!s)
		return ;
	if (!f)
		return ;
	while (s[index])
	{
		f(index, &s[index]);
		index++;
	}
}
