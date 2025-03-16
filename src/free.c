/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:26:20 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/16 12:43:30 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_envp(t_envp *envp)
{
	t_envp	*tmp;

	while (envp)
	{
		free(envp->key);
		free(envp->value);
		tmp = envp;
		envp = envp->next;
		free(tmp);
	}
	free(envp);
}

bool	unset_node(t_envp *envp, char *key)
{
	t_envp	*prev;

	prev = envp;
	while (envp)
	{
		if (ft_str_equals(envp->key, key))
		{
			prev->next = envp->next;
			free(envp->key);
			free(envp->value);
			free(envp);
			return (true);
		}
		prev = envp;
		envp = envp->next;
	}
	return (false);
}
