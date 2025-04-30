#include "minishell.h"

int	cmd_exit(t_smash *smash, char **input)
{
	(void) smash;
	(void) input;
	if (input[1] && !ft_strncmp(input[1], "-", 1))
		return (ft_putstr_fd("smash: export: -: invalid option\n", 2), 2);
	ft_printf("exit\n");
	if (input[1] && input[2])
		return (ft_printf_fd(2, "smash: exit: too many arguments\n"), 2);
	if (input[1]) //TODO: better atoi
		return (ft_printf_fd(2, "smash: exit: %s: numeric argument required\n", input[1]), 2);
	exit(0);
	return (0);
}
