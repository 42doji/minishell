/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:46:57 by junmin            #+#    #+#             */
/*   Updated: 2024/11/10 13:51:01 by junmin           ###   ########.fr       */
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

void tokenizer(t_minishell *mini)
{
	int i;
	t_token *new;
	t_token *temp = NULL;

	i = 0;
	while (mini->input[i])
	{
		new = malloc(sizeof(t_token));
		if (!new)
			return; // malloc 실패 시 오류 처리
		init_token(new);
		new->value = ft_strdup(mini->input[i]);
		set_token_type(mini, i, new);
		new->index = i;

		// 연결 리스트에 추가
		if (temp)
			temp->next = new;
		else
			mini->token = new;

		new->prev = temp;
		temp = new;
		i++;
	}
	// 연결 리스트 끝 표시
	if (temp)
		temp->next = NULL;
}
