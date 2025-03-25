#include "minishell.h"

void	debug_tokens(t_smash *smash)
{
	t_token	*iter;

	iter = smash->first_token;
	while (iter)
	{
		debug_string(*smash, "Token value", iter->value);
		debug_int(*smash, "Token type", iter->type);
		iter = iter->next;
	}
}

//TODO error malloc
void	add_token(t_smash *smash, char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = value;
	token->type = type;
	token->next = NULL;
	if (!smash->last_token)
	{
		smash->first_token = token;
		smash->last_token = token;
	}
	else
	{
		smash->last_token->next = token;
		smash->last_token = token;
	}
}

bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_end_token(char c, t_token_type token_type)
{
	if (token_type == SINGLE_QUOTE)
		return (c == '\'');
	else if (token_type == DOUBLE_QUOTE)
		return (c == '"');
	else if (token_type == HEREDOC)
		return (c != '<');
	else if (token_type == APPEND)
		return (c != '>');
	else if (token_type == INPUT || token_type == OUTPUT || token_type == PIPE)
		return (true);
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0'
		|| c == '\'' || c == '"' || c == '<' || c == '>' || c == '|');
}

t_token_type	get_token_type(char first, char second)
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

void	tokenize(t_smash *smash)
{
	int				iter;
	int				start_token;
	t_token_type	token_type;

	iter = 0;
	start_token = -1;
	token_type = get_token_type(smash->user_input[iter], smash->user_input[iter + 1]);
	while (smash->user_input[iter])
	{
		if (start_token == -1 && !is_space(smash->user_input[iter]))
		{
			token_type = get_token_type(smash->user_input[iter], smash->user_input[iter + 1]);
			if (token_type == SINGLE_QUOTE || token_type == DOUBLE_QUOTE)
				iter++;
			start_token = iter;

		}
		if (start_token != -1 && is_end_token(smash->user_input[iter + 1], token_type))
		{
			add_token(smash, ft_substr(smash->user_input, start_token, iter - start_token + 1), token_type);
			//TODO error malloc
			if (token_type == SINGLE_QUOTE || token_type == DOUBLE_QUOTE)
				iter++;
			start_token = -1;
		}
		iter++;
	}
	//TODO error unclosed quotes
	if (start_token != -1)
		ft_printf_fd(STDERR_FILENO, "smash: unclosed quotes\n");
}

void	read_line(t_smash *smash)
{

	smash->user_input = readline("\e[1;35mSMASH -> \e[0m");
	if (!smash->user_input)
		return ;
	debug_string(*smash, "line", smash->user_input);
	tokenize(smash); //TODO empty before callong read_line
	debug_tokens(smash);
	if (ft_strlen(smash->user_input) > 0)
		add_history(smash->user_input);
}
