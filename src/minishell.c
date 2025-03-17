/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-olm <pdel-olm@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:07:58 by pdel-olm          #+#    #+#             */
/*   Updated: 2025/03/17 18:13:41 by pdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_smash	smash;

	ft_printf("Minishell\n");
	smash.debug_mode = argc > 1 && ft_str_equals(argv[1], "debug");
	smash.envp = init_envp(envp);
	if (!smash.envp)
		return (0); //TODO: Handle error
	while (true)
	{
		read_line(&smash);
		if (!smash.user_input)
			break ;
		char **split = ft_split(smash.user_input, ' ');
		input_handler(&smash, split);
		free(split);
		free(smash.user_input);
	}
	free_t_envp(smash.envp);
	rl_clear_history();
}
