#include "minishell.h"
#include <sys/ioctl.h>

static void	init_sigquit(void);
static void	new_line(void);
static void	init_sigint(void);

void	sig_init(void)
{
	init_sigquit(); // Ctrl + \ //
	init_sigint(); // Ctrl + C //
}

static void	init_sigquit(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	init_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = new_line;
	sigaction(SIGINT, &sa, NULL);
}

static void	new_line(void)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}
