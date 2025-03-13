/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:14:23 by pdel-olm          #+#    #+#             */
/*   Updated: 2025/03/13 02:55:42 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

// envlist.c
void	display_envp(t_envp *envp);
t_envp	*new_node(char *key, char *value);
void	addnode_front(t_envp *node, t_envp **envp);
void	addnode_back(t_envp *node, t_envp **envp);
char	**split_char(char *envp, char c);
t_envp	*init_envp(char	**envp);

// free.c
void	free_t_envp(t_envp *envp);


#endif