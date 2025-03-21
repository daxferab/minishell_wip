/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:05:25 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/18 21:10:05 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(t_envp *envp, char *key)
{
	while (envp)
	{
		if (ft_str_equals(envp->key, key))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

bool	new_entry(t_envp **envp, char *key, char *value)
{
	t_envp	*node;

	node = new_node(key, value);
	if (!node)
		return (false);
	addnode_front(node, envp);
	return (true);
}

bool	update_envp(t_envp **envp, char *key, char *newvalue)
{
	t_envp	*current;

	if (!get_value(*envp, key))
		return (false);
	current = *envp;
	while (current)
	{
		if (ft_str_equals(current->key, key))
		{
			free(current->value);
			current->value = ft_strdup(newvalue);
			if (!current->value)
				return (free(key), false);
			free(key);
			free(newvalue);
			return (true);
		}
		current = current->next;
	}
	return (true);
}

void	display_envp(t_envp *envp)
{
	while (envp)
	{
		ft_printf("%s=%s\n", envp->key, envp->value);
		envp = envp->next;
	}
}

t_envp	*init_envp(char **envp)
{
	int		i;
	char	**sp_envp;
	t_envp	*struct_envp;

	i = 0;
	struct_envp = NULL;
	while (envp[i])
	{
		sp_envp = split_char(envp[i], '=');
		if (!sp_envp)
			return (NULL);
		if (!new_entry(&struct_envp, sp_envp[0], sp_envp[1]))
			return (ft_free_double_pointer((void **)sp_envp), NULL);
		free(sp_envp);
		i++;
	}
	return (struct_envp);
}
