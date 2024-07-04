#include "../includes/minishell.h"

void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_sigquit(int sig)
{
	(void)sig;
}

void handle_eof(void) {
	write(STDOUT_FILENO, "exit\n", 5);
	exit(0);
}

void init_signal_handlers(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}