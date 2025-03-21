/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:10:22 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/20 21:10:47 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
