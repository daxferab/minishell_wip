#include "minishell.h"

//FIXME: Export without arguments
bool	cmd_export(t_smash *smash, char **input)
{
	int		i;
	char	**entry;

	i = 0;
	if (input[1] && !ft_strncmp(input[1], "-", 1))
		return (false);
	while (input[i])
	{
		entry = split_char(input[i], '=');
		if (entry && is_valid_key(entry[0]))
		{
			if (!get_value(smash->envp, entry[0]))
			{
				if (!new_entry(&smash->envp, entry[0], entry[1]))
					return (false);
				return (free(entry), true);
			}
			update_envp(&(smash->envp), entry[0], entry[1]);
			free(entry);
		}
		i++;
	}
	return (true);
}
