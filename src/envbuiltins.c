/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envbuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:52:25 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/20 11:01:18 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	cmd_env(t_smash	smash, char **input)
{
	if (input[1])
		return (false);
	display_envp(smash.envp);
	return (true);
}

bool	cmd_pwd(t_smash *smash, char **input)
{
	if (input[1] && !ft_strncmp(input[1], "-", 1))
		return (false);
	if (smash->cwd)
		free(smash->cwd);
	smash->cwd = getcwd(NULL, 0);
	if (smash->cwd)
		printf("%s\n", smash->cwd);
	return (true);
}

bool	cmd_unset(t_smash *smash, char **input)
{
	int	i;

	i = 0;
	if (!smash->envp)
		return (false);
	if (input[1] && !ft_strncmp(input[1], "-", 1))
		return (false);
	while (input[i])
	{
		if (get_value(smash->envp, input[i]))
			free_node(smash->envp, input[i]);
		i++;
	}
	return (true);
}

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
// export a=c -> if "a" exists, update value to "c"
// 			  -> if "a" does not exist, create and equal to "c"
// export a	  -> nothing
// export	  -> nothing
// export a=c b=d -> exec both (like first example)
// export a=c=b	  -> a = b=c (key is whats before the 1st "=")
// export	  -> declare -x KEY=VALUE
// Reserved icons(for the key) -> "-" "=" "." "$"
