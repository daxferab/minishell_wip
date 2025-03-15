/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:14:23 by pdel-olm          #+#    #+#             */
/*   Updated: 2025/03/15 01:38:34 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_smash
{
	bool	debug_mode;
	t_envp	*envp;
}	t_smash;

// DEBUG

void	debug_int(t_smash smash, char *variable, int value);
void	debug_string(t_smash smash, char *variable, char *value);


// envlist.c
void	update_envp(t_envp *envp, char	*key, char	*newvalue);
void	display_envp(t_envp *envp);
t_envp	*new_node(char *key, char *value);
void	addnode_front(t_envp *node, t_envp **envp);
char	**split_char(char *envp, char c);
t_envp	*init_envp(char	**envp);

// free.c
void	free_t_envp(t_envp *envp);


#endif