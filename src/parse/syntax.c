#include "minishell.h"

//TODO syntax error, but where?
bool	syntax(t_smash *smash)
{
	t_token	*iter;

	if ((smash->first_token && smash->first_token->type == PIPE)
		|| (smash->last_token && smash->last_token->type == PIPE))
		return (false);
	iter = smash->first_token;
	while (iter)
	{
		if (iter->type == PIPE && (!iter->next || iter->next->type == PIPE))
			return (false);
		if (is_redirection(iter->type)
			&& (!iter->next || !is_word(iter->next->type)))
			return (false);
		iter = iter->next;
	}
	return (true);
}
