/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:05:25 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/15 17:38:49 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(t_envp *envp, char *key)
{
	while (!ft_str_equals(envp->key, key)) //FIXME: return "" when key not found
		envp = envp->next;
	return(envp->value);
}

void	update_envp(t_envp *envp, char	*key, char	*newvalue)
{
	while (!ft_str_equals(envp->key, key))
		envp = envp->next;
	free(envp->value);
	envp->value = ft_strdup(newvalue);
}

void	display_envp(t_envp *envp)
{
	while (envp)
	{
		printf("%s=%s\n", envp->key, envp->value);
		envp = envp->next;
	}
}

t_envp	*new_node(char *key, char *value)
{
	t_envp	*newnode;

	newnode = malloc(sizeof(t_envp));
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
	key = malloc(sizeof(char) * (keysize + 1)); //TODO: Protect key
	ft_strlcpy(key, envp, keysize + 1);
	value = ft_strdup(equal_pos + 1); //TODO: Protect value
	splitted = malloc(sizeof(char *) * 3); //TODO: Protect splitted
	splitted[0] = key;
	splitted[1] = value;
	splitted[2] = NULL;
	return (splitted);
}

t_envp	*init_envp(char	**envp)
{
	//TODO: last line has to show the last executed cmd (update on every exec)
	int		i;
	char	**sp_envp;
	t_envp	*struct_envp;
	t_envp	*node;

	i = 0;
	struct_envp = NULL;
	while (envp[i])
	{
		sp_envp = split_char(envp[i], '=');
		node = new_node(sp_envp[0], sp_envp[1]);
		addnode_front(node, &struct_envp);
		free(sp_envp);
		i++;
	}
	return (struct_envp);
}
