/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-olm <pdel-olm@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:52:04 by pdel-olm          #+#    #+#             */
/*   Updated: 2025/03/14 12:58:01 by pdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_int(t_smash smash, char *variable, int value)
{
	if (!smash.debug_mode || !variable)
		return ;
	ft_putstr_fd("\e[3;33m", STDERR_FILENO);
	ft_putstr_fd(variable, STDERR_FILENO);
	ft_putstr_fd(" -> ", STDERR_FILENO);
	ft_putnbr_fd(value, STDERR_FILENO);
	ft_putendl_fd("\e[0m", STDERR_FILENO);
}

void	debug_string(t_smash smash, char *variable, char *value)
{
	if (!smash.debug_mode || !variable)
		return ;
	if (!value)
		return (debug_string(smash, variable, PRINT_NULL_STRING));
	ft_putstr_fd("\e[3;33m", STDERR_FILENO);
	ft_putstr_fd(variable, STDERR_FILENO);
	ft_putstr_fd(" -> ", STDERR_FILENO);
	ft_putstr_fd(value, STDERR_FILENO);
	ft_putendl_fd("\e[0m", STDERR_FILENO);
}
