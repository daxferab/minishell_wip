#include "minishell.h"

void	clear_input(t_smash *smash)
{
	t_token	*iter;
	t_token	*next;

	iter = smash->first_token;
	while (iter)
	{
		next = iter->next;
		free(iter->value);
		free(iter);
		iter = next;
	}
	smash->first_token = NULL;
	smash->last_token = NULL;
	free(smash->user_input);
}
