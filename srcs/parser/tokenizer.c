/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:46:57 by junmin            #+#    #+#             */
/*   Updated: 2024/11/15 23:59:29 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_token_type(t_minishell *mini, int i, t_token *token)
{
	int		result;

	result = check_quote(mini, i, token);
	if (result == 0)
		result = check_pipe(mini->input[i], token);
	if (result == 0)
		result = check_redirect_in(mini->input[i], token);
	if (result == 0)
		result = check_redirect_out(mini->input[i], token);
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

void	tokenizer(t_minishell *mini)
{
	int		i;
	t_token	*new;
	t_token	*temp;

	i = 0;
	temp = NULL;
	new = malloc(sizeof(t_token));
	while (mini->input[i])
	{
		init_token(new);
		set_token_type(mini, i, new);
		replace_env_var(mini, i);
		new->value = ft_strdup(mini->input[i]);
		new->index = i;
		if (temp != NULL)
			new->prev = temp;
		else
			mini->token = new;
		if (mini->input[i + 1])
			new->next = malloc(sizeof(t_token));
		temp = new;
		new = new->next;
		i++;
	}
}
