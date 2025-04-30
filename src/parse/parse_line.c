#include "minishell.h"

bool	parse_line(t_smash *smash)
{
	smash->user_input = readline("\e[1;38;5;99mSMASH -> \e[0m");
	if (!smash->user_input || !smash->user_input[0])
		return (false);
	add_history_entry(smash);
	if (!tokenize(smash))
	{
		ft_putstr_fd("Error tokenizing\n", 2);
		free_smash(*smash);
		exit(1);
	}
	if (!expand_variables(smash) || !remove_quotes(smash))
	{
		ft_putstr_fd("Malloc error\n", 2);
		free_smash(*smash);
		exit(1);
	}
	if (!syntax(smash))
	{
		ft_printf_fd(STDERR_FILENO, "smash: syntax error\n");
		return (clear_input(smash), false);
	}
	parse_pipeline(smash); //TODO: protect
	return (true);
}
