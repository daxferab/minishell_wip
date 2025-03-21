/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:07:58 by pdel-olm          #+#    #+#             */
/*   Updated: 2025/03/18 21:10:38 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_smash	init(int argc, char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_smash	smash;
	char	**split;

	smash = init(argc, argv, envp);
	while (true)
	{
		read_line(&smash);
		if (!smash.user_input)
			break ;
		split = ft_split(smash.user_input, ' ');
		input_handler(&smash, split);
		ft_free_double_pointer((void **)split);
		free(smash.user_input);
	}
	free_smash(smash);
	return (0);
}

static t_smash	init(int argc, char **argv, char **envp)
{
	t_smash	smash;

	ft_printf("Minishell\n");
	smash.debug_mode = argc > 1 && ft_str_equals(argv[1], "debug");
	smash.envp = init_envp(envp);//TODO: Handle error
	smash.cwd = getcwd(NULL, 0);
	return (smash);
}
