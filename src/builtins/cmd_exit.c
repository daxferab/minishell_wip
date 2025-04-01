#include "minishell.h"

//TODO whole fuction
int	cmd_exit(t_smash *smash, char **input)
{
	(void) smash;
	(void) input;
	ft_printf("exit\n");
	exit(0);
	return (0);
}
