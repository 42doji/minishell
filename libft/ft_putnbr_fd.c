/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:59:09 by junmin            #+#    #+#             */
/*   Updated: 2024/03/03 11:23:25 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	nbr;
	char		cast;
	long long	div;

	if (n == 0)
		ft_putchar_fd('0', fd);
	nbr = (long long)n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr *= -1;
	}
	div = 1;
	while (n != 0)
	{
		n /= 10;
		div *= 10;
	}
	while (div > 1)
	{
		div /= 10;
		cast = nbr / div + '0';
		ft_putchar_fd(cast, fd);
		nbr %= div;
	}
}
