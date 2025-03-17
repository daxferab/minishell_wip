/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-olm <pdel-olm@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:14:23 by pdel-olm          #+#    #+#             */
/*   Updated: 2025/03/14 18:08:58 by pdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_smash
{
	char	*user_input;
	bool	debug_mode;
}	t_smash;

// DEBUG

void	debug_int(t_smash smash, char *variable, int value);
void	debug_string(t_smash smash, char *variable, char *value);

//READ_LINE

void	read_line(t_smash *smash);

#endif