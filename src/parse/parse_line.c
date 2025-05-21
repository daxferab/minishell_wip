#include "minishell.h"

void	parse_line(t_smash *smash)
{
	smash->user_input = prompt(smash, false);
	if (!smash->user_input)
		smash->error_type = CTRL_D;
	else if (!smash->user_input[0])
		smash->error_type = EMPTY_PROMPT;
	else
	{
		add_history_entry(smash);
		if (!tokenize(smash) || !expand_variables(smash) || !remove_quotes(smash))
			return ;
		if (!syntax(smash))
			return ;
		if (!parse_pipeline(smash))
			return ;
	}
}
