/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:37:46 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/17 02:10:35 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    t_smash smash;

	ft_printf("Minishell\n");
	smash.debug_mode = argc > 1 && ft_str_equals(argv[1], "debug");
	smash.envp = init_envp(envp);
	if (!smash.envp)
		return (0); //TODO: Handle error
	//display_envp(smash.envp);
	char *input[] = {
		"echo",
		"-n",
		NULL
	};
	//cmd_export(&smash, input);
	// update_envp(smash.envp, "a", "b");
	// display_envp(smash.envp);
	cmd_echo(input);
	free_t_envp(smash.envp);
	return (0);
}
