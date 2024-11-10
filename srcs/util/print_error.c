/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:39:14 by doji              #+#    #+#             */
/*   Updated: 2024/11/10 11:12:46 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *arg, char *message, int exit_status)
{
	char	*str;

	str = ft_strjoin_without_free(arg, message);
	ft_putstr_fd(str, 2);
	free(str);
	g_exit_status = exit_status;
}
