/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmin <junmin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:43:50 by junmin            #+#    #+#             */
/*   Updated: 2024/11/08 16:43:49 by junmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int init_cmd_memory(t_command **cmd)
{
	*cmd = malloc(sizeof(t_command));
	if (!*cmd)
		return 0;

	(*cmd)->cmd = ft_calloc(2, sizeof(char));
	if (!(*cmd)->cmd) {
		free(*cmd);
		return 0;
	}

	(*cmd)->args = ft_calloc(2, sizeof(char *));
	if (!(*cmd)->args) {
		free((*cmd)->cmd);
		free(*cmd);
		return 0;
	}
	return 1;
}

static void init_cmd_values(t_command *cmd, int in_file, int out_file)
{
	cmd->cmd[0] = '\0';
	cmd->args[0] = NULL;
	cmd->exec = 0;
	cmd->in_file = in_file;
	cmd->out_file = out_file;
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->file = NULL;
}

t_command *create_command(int in_file, int out_file)
{
	t_command *cmd;

	if (!init_cmd_memory(&cmd))
		return (NULL);
	init_cmd_values(cmd, in_file, out_file);
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
			result = ft_strjoin(result, var);
			free(var);
		}
		if (!input[*i] || input[*i] == '"')
			return (result);
		str = char_to_string(input[*i]);
		result = ft_strjoin(result, str);
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
