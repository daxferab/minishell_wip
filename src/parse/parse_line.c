#include "minishell.h"

//TODO own file
bool	remove_empty_tokens(t_smash *smash)
{
	t_token	*iter;
	t_token	*previous;
	t_token	*next;

	iter = smash->first_token;
	smash->error_type = EMPTY_PROMPT;
	while (iter)
	{
		next = iter->next;
		if (is_word(iter->type) && !iter->value[0])
		{
			if (iter == smash->first_token)
				smash->first_token = next;
			else
				previous->next = iter->next;
			free_token(iter);
		}
		else
		{
			smash->error_type = OK;
			previous = iter;
		}
		iter = next;
	}
	return (smash->error_type != EMPTY_PROMPT);
}

void	parse_line(t_smash *smash)
{
	clear_input(smash);
	smash->error_type = OK;
	smash->user_input = prompt(smash, false);
	if (!smash->user_input)
		smash->error_type = CTRL_D;
	else
	{
		add_history_entry(smash);
		if (!tokenize(smash))
			return ;
		if (!expand_variables(smash))
			return ;
		if (!syntax(smash))
			return ;
		if (!remove_empty_tokens(smash))
			return ;
		if (!remove_quotes(smash))
			return ;
		if (!parse_pipeline(smash))
			return ;
	}
}
