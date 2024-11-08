/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:43:56 by junmin            #+#    #+#             */
/*   Updated: 2024/11/08 19:51:35 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static void	create_out_dup_list(void)
{
	t_fd		*fd;
	t_command	**temp;
	t_file		*file;
	int			i;

	i = -1;
	fd = (t_fd *)malloc(sizeof(t_fd));
	g_minishell.fd = fd;
	temp = g_minishell.parsed;
	while (temp[++i])
	{
		file = temp[i]->file;
		while (file)
		{
			fd->out = dup(STDOUT_FILENO);
			fd->in = dup(STDIN_FILENO);
			if (file->next || temp[i + 1])
				fd->next = (t_fd *)malloc(sizeof(t_fd));
			else
				fd->next = NULL;
			fd = fd->next;
			file = file->next;
		}
	}
}

static void	process_redirection(t_token **token, t_command **cur)
{
	t_file	*file;
	t_file	*tmp_list;

	tmp_list = (*cur)->file;
	file = (t_file *)malloc(sizeof(t_file));
	file->next = NULL;
	file->type = (*token)->type;
	(*token) = (*token)->next;
	file->name = ft_strdup((*token)->value);
	if (!tmp_list)
		(*cur)->file = file;
	else
	{
		while (tmp_list->next)
			tmp_list = tmp_list->next;
		tmp_list->next = file;
	}
	(*token) = (*token)->next;
}

static t_command	*create_next_command(t_token **tkns, t_command **olds)
{
	t_command	*new_cmd;

	new_cmd = create_command((*olds)->in_file, (*olds)->out_file);
	(*olds)->next = new_cmd;
	new_cmd->prev = (*olds);
	(*tkns) = (*tkns)->next;
	return (new_cmd);
}

static void	add_argument(t_token **token, t_command **cur)
{
	int		i;
	char	**new_arguments;

	i = 0;
	if (!((*cur)->cmd))
	{
		(*cur)->cmd = ft_calloc(ft_strlen((*token)->value) + 2, \
							sizeof(char));
		ft_strcpy((*cur)->cmd, (*token)->value);
	}
	while ((*cur)->args[i])
		i++;
	new_arguments = ft_calloc((i + 2), sizeof(char *));
	new_arguments[i + 1] = NULL;
	new_arguments[i] = ft_strdup((*token)->value);
	while (i--)
		new_arguments[i] = ft_strdup((*cur)->args[i]);
	free_array((*cur)->args);
	(*cur)->args = new_arguments;
	(*token) = (*token)->next;
}

void	parse_command(int in_file, int out_file, t_token *token)
{
	t_command	**list;
	t_command	*cur;

	list = ft_calloc(num_token(g_minishell.input) + 1, sizeof(t_command *));
	while (token)
	{
		cur = create_command(in_file, out_file);
		add_command_to_list(cur, list);
		while (token)
		{
			if (token->type >= 1 && token->type <= 4 && token->next)
				process_redirection(&token, &cur);
			else if (token->type == STRING)
				add_argument(&token, &cur);
			else if (token->type == PIPE && token->next)
			{
				cur = create_next_command(&token, &cur);
				add_command_to_list(cur, list);
			}
			else
				token = token->next;
		}
	}
	g_minishell.parsed = list;
	create_out_dup_list();
}
