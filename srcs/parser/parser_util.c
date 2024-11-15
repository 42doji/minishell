/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:43:50 by junmin            #+#    #+#             */
/*   Updated: 2024/11/15 23:43:25 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_command(int in_file, int out_file)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	cmd->exec = 0;
	cmd->in_file = in_file;
	cmd->out_file = out_file;
	cmd->cmd = ft_calloc(2, sizeof(char));
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->file = NULL;
	cmd->args = ft_calloc(2, sizeof(char *));
	return (cmd);
}

void	add_command_to_list(t_command *current_command, t_command **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	list[i] = current_command;
	list[i + 1] = NULL;
}

int	skip_quote(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

char	*check_quote_double(char **env, char *input, int *i)
{
	char	*str;
	char	*result;
	char	*var;

	result = ft_strdup("");
	(*i)++;
	while (input[*i] != '"')
	{
		while (input[*i] == '$')
		{
			(*i)++;
			var = handle_env_var(env, input, i);
			str = result;
			result = ft_strjoin(str, var);
			free(var);
			free(str);
		}
		if (!input[*i] || input[*i] == '"')
			return (result);
		var = char_to_string(input[*i]);
		str = result;
		result = ft_strjoin(str, var);
		free(var);
		free(str);
		(*i)++;
	}
	if (input[*i] == '"')
		(*i)++;
	return (result);
}

char	*check_quote_single(char *input, int *i)
{
	char	*result;
	int		j;

	(*i)++;
	j = *i;
	while (input[*i] != '\'')
	{
		(*i)++;
	}
	if (input[*i] == '\'')
		(*i)++;
	result = ft_substr(input, j, (*i - j) - 1);
	return (result);
}
