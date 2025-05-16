#include "minishell.h"

bool	parse_line(t_smash *smash)
{
	smash->user_input = prompt(smash, false);
	if (!smash->user_input || !smash->user_input[0])
		smash->error_type = EMPTY_PROMPT;
	else
	{
		add_history_entry(smash);
		if (!tokenize(smash) || !expand_variables(smash) || !remove_quotes(smash))
			return (ft_putstr_fd("Internal error\n", 2), clear_input(smash), false);
		if (!syntax(smash))
			return (true); //TODO: Handle syntax error
		if (!parse_pipeline(smash))
			return (ft_putstr_fd("Internal error\n", 2), clear_input(smash), false);
	}
	return (true);
}
