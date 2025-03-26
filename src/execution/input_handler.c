#include "minishell.h"

void	input_handler(t_smash *smash, char **input)
{
	if (ft_str_equals(input[0], "env"))
		smash->exit_status = cmd_env(*smash, input);
	else if (ft_str_equals(input[0], "pwd"))
		smash->exit_status = cmd_pwd(smash, input);
	else if (ft_str_equals(input[0], "unset"))
		smash->exit_status = cmd_unset(smash, input);
	else if (ft_str_equals(input[0], "export")) //TODO: return status
		smash->exit_status = cmd_export(smash, input);
	else if (ft_str_equals(input[0], "echo"))
		smash->exit_status = cmd_echo(input);
	else if (ft_str_equals(input[0], "cd")) //TODO: return status
		cmd_cd(smash, input);
	else if (ft_str_equals(input[0], "exit")) //TODO: return status
		exit(0);
	// else
	// 	execute(); //TODO: Create function
}
