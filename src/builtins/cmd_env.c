#include "minishell.h"

int	cmd_env(t_smash	smash, char **input)
{
	if (input[1])
		return (2);
	display_envp(smash.envp);
	return (0);
}
