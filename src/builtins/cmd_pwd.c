#include "minishell.h"


int	cmd_pwd(t_smash *smash, char **input)
{
	if (input[1] && !ft_strncmp(input[1], "-", 1))
		return (2);
	if (smash->cwd)
		free(smash->cwd);
	smash->cwd = getcwd(NULL, 0);
	if (smash->cwd)
		return (printf("%s\n", smash->cwd), 0);
	return (1);
}
