/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:05:25 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/15 20:06:06 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envsize(t_envp *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 1;
	while (lst->next)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

char	*get_value(t_envp *envp, char *key)
{
	while (envp)
	{
		if (ft_str_equals(envp->key, key))
			return (envp->value);
		envp = envp->next;
	}
	return(NULL);
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

bool	update_envp(t_envp *envp, char	*key, char	*newvalue)
{
	if (!get_value(envp, key))
	{
		if (!new_entry(&envp, key, newvalue))
			return (false);
		return (true);
	}
	while (!ft_str_equals(envp->key, key))
		envp = envp->next;
	free(envp->value);
	envp->value = ft_strdup(newvalue);
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

t_envp	*new_node(char *key, char *value)
{
	t_envp	*newnode;

	newnode = malloc(sizeof(t_envp));
	if (!newnode)
		return (NULL);
	newnode->key = key;
	newnode->value = value;
	newnode->next = NULL;
	return (newnode);
}

void	addnode_front(t_envp *node, t_envp **envp)
{
	node->next = *envp;
	*envp = node;
}

char	**split_char(char *envp, char c)
{
	int		keysize;
	char	*key;
	char	*value;
	char	*equal_pos;
	char	**splitted;
	
	equal_pos = ft_strchr(envp, c);
	keysize = equal_pos - envp;
	key = malloc(sizeof(char) * (keysize + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, envp, keysize + 1);
	value = ft_strdup(equal_pos + 1);
	if (!value)
		return (free(key), NULL);
	splitted = malloc(sizeof(char *) * 3);
	if (!splitted)
		return (free(key), free(value), NULL);
	splitted[0] = key;
	splitted[1] = value;
	splitted[2] = NULL;
	return (splitted);
}

t_envp	*init_envp(char	**envp)
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
