/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:26:20 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/14 02:32:39 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_envp(t_envp *envp)
{
	t_envp	*tmp;

	while(envp)
	{
		free(envp->key);
		free(envp->value);
		tmp = envp;
		envp = envp->next;
		free(tmp);
	}
	free(envp);
}
