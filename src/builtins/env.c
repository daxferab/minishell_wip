/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:52:25 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/26 17:15:14 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_env(t_smash	smash, char **input)
{
	if (input[1])
		return (2);
	display_envp(smash.envp);
	return (0);
}
