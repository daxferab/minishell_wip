#include "minishell.h"


static bool	has_valid_args(char **input);

//FIXME: Export without arguments
int	cmd_export(t_smash *smash, char **input)
{
	int		i;
	char	**entry;

	i = 1;
	if (!has_valid_args(input))
		return (2);
	while (input[i])
	{
		entry = split_char(input[i], '=');
		if (entry && is_valid_key(entry[0]))
		{
			if (!get_value(smash->envp, entry[0]))
			{
				if (!new_entry(&smash->envp, entry[0], entry[1]))
					return (ft_free_double_pointer((void **)entry), ft_putstr_fd("Malloc error\n", 2), -1);
				return (free(entry), 0);
			}
			if (!update_envp(&(smash->envp), entry[0], entry[1]))
				return (ft_free_double_pointer((void **)entry), ft_putstr_fd("Malloc error\n", 2), -1);
			ft_free_double_pointer((void **)entry);
		}
		i++;
	}
	return (0);
}

static bool	has_valid_args(char **input)
{
	if (input[1] && !ft_strncmp(input[1], "-", 1))
		return (ft_putstr_fd("smash: export: -: invalid option\n", 2), false);
	if (!input[1])
		return (ft_putstr_fd("smash: export: missing operand\n", 2), false);
	return (true);
}
