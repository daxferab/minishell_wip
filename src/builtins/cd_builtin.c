#include "minishell.h"

static void	update_wd(t_smash *smash);
static int	array_len(char **array);

bool	cmd_cd(t_smash *smash, char **input)
{
	int	cmd_len;

	cmd_len = array_len(input);
	if (cmd_len > 2) //too many args
		return (false);
	if (cmd_len == 1) //no args
	{
		if (!get_value(smash->envp, "HOME"))
			return (false); //HOME not set
		if (chdir(get_value(smash->envp, "HOME")) == -1)
			return (false); //error changing directory
		update_wd(smash);
		return (true);
	}
	if (access(input[1], F_OK | X_OK) == -1) //file does not exist
		return (false); // Not an existing directory
	if (chdir(input[1]) == -1) //error changing directory
		return (false);
	update_wd(smash);
	return (true);
}

static void	update_wd(t_smash *smash) //FIXME
{
	update_envp(&smash->envp, "OLDPWD", get_value(smash->envp, "PWD"));
	// update_envp(&smash->envp, "OLDPWD", "");
	// if (smash->cwd)
	// 	free(smash->cwd);
	// smash->cwd = getcwd(NULL, 0);
	// if (get_value(smash->envp, "PWD"))
	// 	update_envp(&smash->envp, "PWD", smash->cwd);
}

static int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
