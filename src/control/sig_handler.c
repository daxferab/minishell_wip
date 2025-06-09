#include "minishell.h"

volatile sig_atomic_t	g_heredoc_interrupted = 0;

static void	handle_sigquit(void);
static void	handle_sigint(void);
static void	new_line(int sig);

void	sig_handler(void)
{
	handle_sigquit();
	handle_sigint();
}

static void	handle_sigquit(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	handle_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = new_line;
	sigaction(SIGINT, &sa, NULL);
}

static void	new_line(int sig)
{
	(void) sig;
	g_heredoc_interrupted = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}
