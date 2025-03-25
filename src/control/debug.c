#include "minishell.h"

void	debug_int(t_smash smash, char *variable, int value)
{
	if (!smash.debug_mode || !variable)
		return ;
	ft_putstr_fd("\e[3;33m", STDERR_FILENO);
	ft_putstr_fd(variable, STDERR_FILENO);
	ft_putstr_fd(" -> ", STDERR_FILENO);
	ft_putnbr_fd(value, STDERR_FILENO);
	ft_putendl_fd("\e[0m", STDERR_FILENO);
}

void	debug_string(t_smash smash, char *variable, char *value)
{
	if (!smash.debug_mode || !variable)
		return ;
	if (!value)
		return (debug_string(smash, variable, PRINT_NULL_STRING));
	ft_putstr_fd("\e[3;33m", STDERR_FILENO);
	ft_putstr_fd(variable, STDERR_FILENO);
	ft_putstr_fd(" -> ", STDERR_FILENO);
	ft_putstr_fd(value, STDERR_FILENO);
	ft_putendl_fd("\e[0m", STDERR_FILENO);
}
