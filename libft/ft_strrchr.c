/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:58:08 by junmin            #+#    #+#             */
/*   Updated: 2024/02/27 21:44:15 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*result;
	char	*temp;

	result = 0;
	temp = (char *)s;
	while (*temp)
	{
		if (c == *temp)
			result = temp;
		temp++;
	}
	if (*temp == c)
		result = temp;
	return (result);
}
