/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:46:57 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 11:17:03 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_char_special(char *str, int k, t_token *token)
{
	int		result;

	result = check_quote(k, token);
	if (result == 0)
		result = check_pipe(str, token);
	if (result == 0)
		result = check_redirect_in(str, token);
	if (result == 0)
		result = check_redirect_out(str, token);
	if (result == 0)
		token->type = STRING;
}

static void	init_token(t_token *token)
{
	token->value = NULL;
	token->index = 0;
	token->prev = NULL;
	token->next = NULL;
}

void	tokenizer(char **str)
{
	int		i;
	t_token	*new;
	t_token	*temp;

	i = 0;
	temp = NULL;
	new = malloc(sizeof(t_token));
	while (str[i])
	{
		init_token(new);
		new->value = ft_strdup(str[i]);
		check_char_special(str[i], i, new);
		new->index = i;
		if (temp != NULL)
			new->prev = temp;
		else
			g_minishell.token = new;
		if (str[i + 1])
			new->next = malloc(sizeof(t_token));
		temp = new;
		new = new->next;
		i++;
	}
}
