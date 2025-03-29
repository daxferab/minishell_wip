#include "minishell.h"

static void	clear_vars(t_token *token)
{
	t_var	*iter;
	t_var	*next;

	iter = token->first_variable;
	while (iter)
	{
		next = iter->next;
		free(iter->value);
		free(iter);
		iter = next;
	}
}

void	clear_input(t_smash *smash)
{
	t_token	*iter;
	t_token	*next;

	iter = smash->first_token;
	while (iter)
	{
		next = iter->next;
		clear_vars(iter);
		free(iter->value);
		free(iter);
		iter = next;
	}
	smash->first_token = NULL;
	smash->last_token = NULL;
	free(smash->user_input);
}
