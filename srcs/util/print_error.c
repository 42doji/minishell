/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:39:14 by doji              #+#    #+#             */
/*   Updated: 2024/11/08 19:46:48 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

void	print_error(char *arg, char *message, int exit_status)
{
	char	*str;

	str = ft_strjoin_without_free(arg, message);
	ft_putstr_fd(str, 2);
	free(str);
	g_minishell.exit_status = exit_status;
}
