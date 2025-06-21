#include "minishell.h"

bool	g_heredoc_interrupted = false;

static void	handle_sigint(int sig);

bool	sig_handler(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (false);
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		return (false);
	return (true);
}

/*
ioctl(1, TIOCSTI, "\n")
inyecta un carácter en la entrada del terminal.
se simula que el usuario presionó Enter para que el shell siga funcionando.

rl_on_new_line()
Indica que el cursor está en una nueva línea (evita problemas de visualización).

rl_replace_line("", 0)
Borra el contenido de la línea actual en Readline
*/

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_heredoc_interrupted = true;
		ioctl(1, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
