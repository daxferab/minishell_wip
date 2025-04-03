#include "minishell.h"

bool	is_redirection(t_token_type type)
{
	return (type == INPUT || type == HEREDOC
		|| type == OUTPUT || type == APPEND);
}

bool	is_word(t_token_type type)
{
	return (type == LITERAL || type == SINGLE_QUOTE || type == DOUBLE_QUOTE);
}
