/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:25:07 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/26 16:27:21 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_unset(t_smash *smash, char **input)
{
	int	i;

	i = 0;
	if (!smash->envp)
		return (127);
	if (input[1] && !ft_strncmp(input[1], "-", 1))
		return (127);
	while (input[i])
	{
		if (get_value(smash->envp, input[i]))
			free_node(smash->envp, input[i]);
		i++;
	}
	return (0);
}
