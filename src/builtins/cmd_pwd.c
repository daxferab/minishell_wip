#include "minishell.h"


int	cmd_pwd(t_smash *smash, char **input)
{
	if (input[1] && !ft_strncmp(input[1], "-", 1))
		return (ft_putstr_fd("smash: cd: -: invalid option\n", 2), 2);
	if (smash->cwd)
		free(smash->cwd);
	smash->cwd = getcwd(NULL, 0);
	if (smash->cwd)
		return (ft_printf("%s\n", smash->cwd), 0);
	return (ft_printf_fd(2, "Couldn`t find working directory\n"), 2); //TODO: close or only error msg?
}
