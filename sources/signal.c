#include "minishell.h"

void	handle_quit(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	quit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals(void)
{
	struct sigaction	no_quit;

	// no_quit.sa_handler = handle_quit;
	no_quit.sa_handler = quit;
	no_quit.sa_flags = 0;
	sigemptyset(&no_quit.sa_mask);

	// sigaction(SIGINT, &no_quit, NULL);
	sigaction(SIGQUIT, &no_quit, NULL);
}
