/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:37:46 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/16 01:12:47 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_smash	smash;

	ft_printf("Minishell\n");
	smash.debug_mode = argc > 1 && ft_str_equals(argv[1], "debug");
	smash.envp = init_envp(envp);
	if (!smash.envp)
		free_t_envp(smash.envp);
	display_envp(smash.envp);
	// char	**cmd = malloc(sizeof(char *) * 4);
	// cmd[0] = malloc(sizeof(char) * 6);
	// cmd[0] = "unset";
	// cmd[1] = malloc(sizeof(char) * 6);
	// cmd[1] = "unset";
	// cmd[2] = malloc(sizeof(char) * 22);
	// cmd[2] = "MEMORY_PRESSURE_WRITE";
	// cmd_unset(&smash, cmd);
	// ft_free_double_pointer((void **)cmd);
	// display_envp(smash.envp);
	free_t_envp(smash.envp);
}
