#include "../includes/minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	error_handler(t_error error)
{
	ft_putstr_fd("minishell: ", 2);
	if (error == MALLOC_ERROR)
		ft_putstr_fd(": malloc error\n", 2);
	else if (error == OPEN_ERROR)
		ft_putstr_fd(": open error\n", 2);
	else if (error == CLOSE_ERROR)
		ft_putstr_fd(": close error\n", 2);
	else if (error == READ_ERROR)
		ft_putstr_fd(": read error\n", 2);
	else if (error == WRITE_ERROR)
		ft_putstr_fd(": write error\n", 2);
	else if (error == PIPE_ERROR)
		ft_putstr_fd(": pipe error\n", 2);
	else if (error == FORK_ERROR)
		ft_putstr_fd(": fork error\n", 2);
	else if (error == EXECVE_ERROR)
		ft_putstr_fd(": execve error\n", 2);
	else if (error == WAIT_ERROR)
		ft_putstr_fd(": wait error\n", 2);
	else if (error == REDIRECTION_ERROR)
		ft_putstr_fd(": redirection error\n", 2);
	else if (error == ARGUMENT_ERROR)
		ft_putstr_fd(": argument error\n", 2);
	else if (error == ENV_ERROR)
		ft_putstr_fd(": env error\n", 2);
	else if (error == EXIT_ERROR)
		ft_putstr_fd(": exit error\n", 2);
	else
		ft_putstr_fd("\n", 2);
	exit(error);
}
