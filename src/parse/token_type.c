#include "minishell.h"

t_token_type	get_token_type(char *c)
{
	if (*c == '<' && *(c + 1) && *(c + 1) == '<')
		return (HEREDOC);
	else if (*c == '<')
		return (INPUT);
	else if (*c == '>' && *(c + 1) && *(c + 1) == '>')
		return (APPEND);
	else if (*c == '>')
		return (OUTPUT);
	else if (*c == '|')
		return (PIPE);
	else
		return (LITERAL);
}

bool	is_redirection(t_token_type type)
{
	return (type == INPUT || type == HEREDOC
		|| type == OUTPUT || type == APPEND);
}

bool	is_word(t_token_type type)
{
	return (type == LITERAL || type == SINGLE_QUOTE || type == DOUBLE_QUOTE);
}
