/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:07:58 by pdel-olm          #+#    #+#             */
/*   Updated: 2025/03/18 01:48:00 by daxferna         ###   ########.fr       */
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
	// cmd_pwd(&smash);
	free_smash(smash);
	return (0);
}
