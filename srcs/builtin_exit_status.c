#include "../includes/minishell.h"

int		last_exit_status = 0;

void	update_last_exit_status(int status)
{
	last_exit_status = status;
}

char	*expand_exit_status(char *command)
{
	char	*expanded_command;
	char	*pos;
	char	status_str[12];
	char	*new_command;
	size_t	prefix_len;

	expanded_command = ft_strdup(command);
	if (!expanded_command)
		return (NULL);
	pos = ft_strstr(expanded_command, "$?");
	if (pos)
	{
		sprintf(status_str, "%d", last_exit_status);
		prefix_len = pos - expanded_command;
		new_command = malloc(prefix_len + strlen(status_str) + strlen(pos + 2) + 1);
		if (!new_command)
			return (free(expanded_command), NULL);
		ft_strncpy(new_command, expanded_command, prefix_len);
		ft_strcpy(new_command + prefix_len, status_str);
		ft_strcpy(new_command + prefix_len + strlen(status_str), pos + 2);
		free(expanded_command);
		return (new_command);
	}
	return (expanded_command);
}

/*  사용 예제 코드 */
void execute_command(char *command)
{
	char	*command_with_expanded_status;
	int		command_exit_status;

	command_with_expanded_status = expand_exit_status(command);
	if (!command_with_expanded_status)
	{
		printf("메모리 할당에 실패했습니다.\n");
		return ;
	}
	command_exit_status = system(command_with_expanded_status);
	update_last_exit_status(WEXITSTATUS(command_exit_status));
	free(command_with_expanded_status);
}

void handle_exit_command(char **args)
{
	if (args[1])
	{
		printf("exit: too many arguments\n");
		update_last_exit_status(1);
	}
	else
	{
		update_last_exit_status(0);
		exit(last_exit_status);
	}
}
