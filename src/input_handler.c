/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputhandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:03:56 by daxferna          #+#    #+#             */
/*   Updated: 2025/03/20 12:33:38 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_handler(t_smash *smash, char **input)
{
	if (ft_str_equals(input[0], "env"))
		cmd_env(*smash, input);
	else if (ft_str_equals(input[0], "pwd"))
		cmd_pwd(smash, input);
	else if (ft_str_equals(input[0], "unset"))
		cmd_unset(smash, input);
	else if (ft_str_equals(input[0], "export"))
		cmd_export(smash, input);
	else if (ft_str_equals(input[0], "echo"))
		cmd_echo(input);
	else if (ft_str_equals(input[0], "cd"))
		cmd_cd(smash, input);
	// else if (ft_str_equals(input[0], "exit"))
	// 	cmd_exit(); //TODO: Create function
	// else
	// 	execute(); //TODO: Create function
}
