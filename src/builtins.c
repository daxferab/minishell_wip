/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:52:25 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/16 12:38:25 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_env(t_smash	smash)
{
	display_envp(smash.envp);
}

void	cmd_pwd(t_smash smash)
{
	if (get_value(smash.envp, "PWD"))
		printf("%s\n", get_value(smash.envp, "PWD"));
}

void	cmd_unset(t_smash *smash, char	**cmd) //FIXME
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (get_value(smash->envp, cmd[i]))
			unset_node(smash->envp, cmd[i]);
		i++;
	}
}
