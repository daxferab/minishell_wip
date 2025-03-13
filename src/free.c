/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:26:20 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/13 02:31:31 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_envp(t_envp *envp)
{
	while(envp)
	{
		free(envp->key);
		free(envp->value);
		envp = envp->next;
	}
}
