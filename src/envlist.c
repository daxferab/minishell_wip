/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   envlist.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: daxferna <daxferna@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/12 14:53:59 by daxferna		  #+#	#+#			 */
/*   Updated: 2025/03/12 16:57:10 by daxferna		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void	display_envp(t_envp *envp)
{
	while (envp) //FIXME: Remove last \n
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

void	addnode_back(t_envp *node, t_envp **envp)
{
	t_envp *current;

	if (*envp == NULL)
	{
		*envp = node;
		return;
	}
	current = *envp;
	while(current->next != NULL)
		current = current->next;
	current->next = node;
}

t_envp	*init_envp(char	**envp) 
{
	//FIXME: some lines have more than one "="
	//FIXME: when value or key is empty, it writes (null)
	//FIXME: last line is different
	int		i;
	char	**sp_envp;
	t_envp	*struct_envp;
	t_envp	*node;

	i = 0;
	struct_envp = NULL;
	while (envp[i])
	{
		sp_envp = ft_split(envp[i], '='); //TODO: Protect split
		node = new_node(sp_envp[0], sp_envp[1]);
		addnode_back(node, &struct_envp);
		free(sp_envp);
		i++;
	}
	return (struct_envp);
}
