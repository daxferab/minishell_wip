#include "minishell.h"

static t_token_type	get_token_type(char first, char second);
static bool			is_start_token(int start_token, char c);
static bool			is_end_token(int start_token, char c, t_token_type type);
static bool			tokenize_char(t_smash *smash,
						int *iter, int *start_token, t_token_type *type);

//returns false if malloc fails
bool	tokenize(t_smash *smash)
{
	int				iter;
	int				start_token;
	t_token_type	token_type;

	iter = 0;
	start_token = -1;
	token_type = -1;
	while (smash->user_input[iter])
		tokenize_char(smash, &iter, &start_token, &token_type);
	//TODO error unclosed quotes
	if (start_token != -1)
		ft_printf_fd(STDERR_FILENO, "smash: unclosed quotes\n");
	debug_tokens(smash);
	return (true);
}

static bool	tokenize_char(t_smash *smash,
	int *iter, int *start_token, t_token_type *type)
{
	if (is_start_token(*start_token, smash->user_input[*iter]))
	{
		*type = get_token_type(smash->user_input[*iter],
				smash->user_input[*iter + 1]);
		if (*type == SINGLE_QUOTE || *type == DOUBLE_QUOTE
			|| *type == HEREDOC || *type == APPEND)
			(*iter)++;
		*start_token = *iter;
	}
	if (is_end_token(*start_token, smash->user_input[*iter + 1], *type))
	{
		if (!add_token(smash, *start_token, *iter - *start_token + 1, *type))
			return (false);
		if (*type == SINGLE_QUOTE || *type == DOUBLE_QUOTE)
			(*iter)++;
		*start_token = -1;
	}
	(*iter)++;
	return (true);
}

static t_token_type	get_token_type(char first, char second)
{
	if (first == '\'')
		return (SINGLE_QUOTE);
	else if (first == '"')
		return (DOUBLE_QUOTE);
	else if (first == '<' && second == '<')
		return (HEREDOC);
	else if (first == '<')
		return (INPUT);
	else if (first == '>' && second == '>')
		return (APPEND);
	else if (first == '>')
		return (OUTPUT);
	else if (first == '|')
		return (PIPE);
	else
		return (LITERAL);
}

static bool	is_start_token(int start_token, char c)
{
	return (start_token == -1 && c != ' ' && c != '\t' && c != '\n');
}

static bool	is_end_token(int start_token, char c, t_token_type type)
{
	if (start_token == -1)
		return (false);
	if (type == SINGLE_QUOTE)
		return (c == '\'');
	else if (type == DOUBLE_QUOTE)
		return (c == '"');
	else if (type == LITERAL)
		return (c == ' ' || c == '\t' || c == '\n' || c == '\0'
			|| c == '\'' || c == '"' || c == '<' || c == '>' || c == '|');
	return (true);
}
