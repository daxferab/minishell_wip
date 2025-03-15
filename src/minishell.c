/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:37:46 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/15 15:54:09 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_smash	smash;

	ft_printf("Minishell\n");
	smash.debug_mode = argc > 1 && ft_str_equals(argv[1], "debug");
	debug_int(smash, "argc", argc);
	smash.envp = init_envp(envp);
	free_t_envp(smash.envp);
}
