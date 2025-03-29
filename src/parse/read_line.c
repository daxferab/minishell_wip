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

void	extra(t_smash *smash, int start, int len)
{
	int		user_iter;
	int		token_iter;
	int		value_iter;
	t_var	*var_iter;

	user_iter = start;
	token_iter = 0;
	var_iter = smash->last_token->first_variable;
	while (user_iter < start + len)
	{
		while (var_iter && !var_iter->valid_name)
			var_iter = var_iter->next;
		if (var_iter && user_iter == var_iter->pos)
		{
			value_iter = 0;
			while (value_iter < var_iter->value_len)
				smash->last_token->value[token_iter++] = var_iter->value[value_iter++];
			user_iter += var_iter->key_len;
			var_iter = var_iter->next;
		}
		else
			smash->last_token->value[token_iter++] = smash->user_input[user_iter++];
	}
	smash->last_token->value[token_iter] = 0;
}

void	expand(t_smash *smash, int start, int len)
{
	int	iter;
	int	new_len;

	iter = start;
	new_len = len;
	while (iter < start + len)
	{
		if (smash->user_input[iter] == '$'
			&& !(iter > 0 && smash->user_input[iter - 1] == '$'))
		{
			get_var(smash, iter);
			new_len -= smash->last_token->last_variable->key_len;
			new_len += smash->last_token->last_variable->value_len;
		}
		iter++;
	}
	smash->last_token->value = malloc((new_len + 1) * sizeof(char));// TODO error malloc
	extra(smash, start, len);
}

//TODO error malloc
void	add_token(t_smash *smash, int start, int len, t_token_type type)
{
	if (!smash->first_token)
	{
		smash->first_token = malloc(sizeof(t_token)); //TODO error malloc
		smash->last_token = smash->first_token;
	}
	else
	{
		smash->last_token->next = malloc(sizeof(t_token)); //TODO error malloc
		smash->last_token = smash->last_token->next;
	}
	smash->last_token->first_variable = NULL;
	smash->last_token->last_variable = NULL;
	smash->last_token->value = NULL;
	if (type == SINGLE_QUOTE)
		smash->last_token->value = ft_substr(smash->user_input, start, len); //TODO error malloc
	else if (type == LITERAL || type == DOUBLE_QUOTE)
		expand(smash, start, len); // TODO malloc
	smash->last_token->type = type;
	smash->last_token->next = NULL;
}

bool	is_start_token(int start_token, char c)
{
	return (start_token == -1 && c != ' ' && c != '\t' && c != '\n');
}

bool	is_end_token(int start_token, char c, t_token_type type)
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
	token_type = -1;
	while (smash->user_input[iter])
	{
		if (is_start_token(start_token, smash->user_input[iter]))
		{
			token_type = get_token_type(smash->user_input[iter], smash->user_input[iter + 1]);
			if (token_type == SINGLE_QUOTE || token_type == DOUBLE_QUOTE
				|| token_type == HEREDOC || token_type == APPEND)
				iter++;
			start_token = iter;

		}
		if (is_end_token(start_token, smash->user_input[iter + 1], token_type))
		{
			add_token(smash, start_token, iter - start_token + 1, token_type);
			//TODO error malloc
			if (token_type == SINGLE_QUOTE || token_type == DOUBLE_QUOTE)
				iter++;
			start_token = -1;
		}
		iter++;
	}
	if (start_token != -1) //TODO error unclosed quotes
		ft_printf_fd(STDERR_FILENO, "smash: unclosed quotes\n");
	debug_tokens(smash);
}

void	read_line(t_smash *smash)
{
	smash->user_input = readline("\e[1;35mSMASH -> \e[0m");
	if (!smash->user_input)
		return ;
	//debug_string(*smash, "line", smash->user_input);
	if (ft_strlen(smash->user_input) > 0)
		add_history(smash->user_input);
	tokenize(smash);
	//TODO syntax
}
