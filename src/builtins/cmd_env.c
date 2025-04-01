#include "minishell.h"

int	cmd_env(t_smash	smash, char **input)
{
	if (input[1])
		return (ft_putstr_fd("smash: env: too many args\n", 2), 2);
	display_envp(smash.envp);
	return (0);
}
