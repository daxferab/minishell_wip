#include "minishell.h"

//TODO syntax error, but where?
bool	syntax(t_smash *smash)
{
	t_token	*iter;

	if ((smash->first_token && smash->first_token->type == PIPE)
		|| (smash->last_token && smash->last_token->type == PIPE))
		return (ft_printf_fd(STDERR_FILENO, "smash: syntax error near '|'\n"), false);
	iter = smash->first_token;
	while (iter)
	{
		if (iter->type == PIPE && (!iter->next || iter->next->type == PIPE))
			return (ft_printf_fd(STDERR_FILENO, "smash: syntax error near '|'\n"), false);
		if (is_redirection(iter->type)
			&& (!iter->next || !is_word(iter->next->type)))
			return (ft_printf_fd(STDERR_FILENO, "smash: syntax error near '%s'\n", NULL), false); //TODO: Print next token
		iter = iter->next;
	}
	return (true);
}
