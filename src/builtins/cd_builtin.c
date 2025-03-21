/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:28 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/21 19:19:21 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	cmd_cd(t_smash *smash, char **input) //FIXME
{
	if (input[2]) //too many args
		return (false);
	if (!input[1]) 
	{
		if (!get_value(smash->envp, "HOME"))
			return (false);
		chdir(get_value(smash->envp, "HOME"));
		update_envp(&smash->envp, "OLDPWD", smash->cwd);
		if (smash->cwd)
			free(smash->cwd);
		smash->cwd = getcwd(NULL, 0);
		update_envp(&smash->envp, "PWD", smash->cwd);
		return (true);
	}
	if (access(input[1], F_OK | X_OK) == -1) //file does not exist
		return (false);
	if (chdir(input[1]) == -1) //error changing directory
		return (false);
	update_envp(&smash->envp, "OLDPWD", smash->cwd);
	if (smash->cwd)
		free(smash->cwd);
	smash->cwd = getcwd(NULL, 0);
	update_envp(&smash->envp, "PWD", smash->cwd);
	return (true);
}
