/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:25:07 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/25 19:25:36 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
