/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:14:23 by pdel-olm          #+#    #+#             */
/*   Updated: 2025/03/16 00:59:26 by daxferna         ###   ########.fr       */
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

// builtins.c
void	cmd_env(t_smash	smash);
void	cmd_pwd(t_smash smash);
void	cmd_unset(t_smash *smash, char	**cmd);

// envlist.c
char	*get_value(t_envp *envp, char *key);
bool	new_entry(t_envp **envp, char *key, char *value);
bool	update_envp(t_envp *envp, char	*key, char	*newvalue);
void	display_envp(t_envp *envp);
t_envp	*init_envp(char	**envp);

//envutils.c
char	**split_char(char *envp, char c);
t_envp	*new_node(char *key, char *value);
void	addnode_front(t_envp *node, t_envp **envp);
int		envsize(t_envp *lst);


// free.c
void	free_t_envp(t_envp *envp);
void	unset_node(t_envp *envp, char *key);

#endif