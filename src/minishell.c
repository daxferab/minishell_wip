/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:07:58 by pdel-olm          #+#    #+#             */
/*   Updated: 2025/03/17 17:15:03 by daxferna         ###   ########.fr       */
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
		"export",
		"PWD=a",
		"hola",
		"hola = a",
		NULL
	};
	cmd_export(&smash, input);
	printf("PWD: %s\n", get_value(smash.envp, "PWD"));
	cmd_unset(&smash, (char *[]){"PWD", NULL});
	cmd_pwd(smash);
	free_t_envp(smash.envp);
	return (0);
}
