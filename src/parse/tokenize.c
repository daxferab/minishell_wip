#include "minishell.h"

static bool			is_start_token(int start_token, char c);
static bool			is_end_token(int start_token, char c, t_token_type type);
static t_token_type	mutate(t_token_type type, char c);

bool	tokenize(t_smash *smash)
{
	int				iter;
	int				start_token;
	t_token_type	type;

	iter = -1;
	start_token = -1;
	while (smash->user_input[++iter])
	{
		if (is_start_token(start_token, smash->user_input[iter]))
		{
			type = get_token_type(&(smash->user_input[iter]));
			if (type == HEREDOC || type == APPEND)
				iter++;
			start_token = iter;
		}
		type = mutate(type, smash->user_input[iter]);
		if (is_end_token(start_token, smash->user_input[iter + 1], type))
		{
			add_token(smash, start_token, iter - start_token + 1, type);
			start_token = -1;
		}
	}
	if (start_token != -1)
		ft_printf_fd(STDERR_FILENO, "smash: unclosed quotes\n");
	return (true);
}

static bool	is_start_token(int start_token, char c)
{
	return (start_token == -1 && c != ' ' && c != '\t' && c != '\n');
}

static bool	is_end_token(int start_token, char c, t_token_type type)
{
	if (start_token == -1 || type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
		return (false);
	else if (type == LITERAL)
		return (c == ' ' || c == '\t' || c == '\n' || c == '\0'
			|| c == '<' || c == '>' || c == '|');
	return (true);
}

t_token_type	mutate(t_token_type type, char c)
{
	if (type == LITERAL && c == '\'')
		return (SINGLE_QUOTE);
	else if (type == LITERAL && c == '"')
		return (DOUBLE_QUOTE);
	else if (type == SINGLE_QUOTE && c == '\'')
		return (LITERAL);
	else if (type == DOUBLE_QUOTE && c == '"')
		return (LITERAL);
	return (type);
}
