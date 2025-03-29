#include "minishell.h"

static bool	get_token_value(t_smash *smash,	
				int start, int len, t_token_type type);
static bool	expand_variables(t_smash *smash, int start, int len);
static void	copy_variables(t_smash *smash, int start, int len);

//returns false if malloc fails
bool	add_token(t_smash *smash, int start, int len, t_token_type type)
{
	if (!smash->first_token)
	{
		smash->first_token = malloc(sizeof(t_token));
		if (!smash->first_token)
			return (false);
		smash->last_token = smash->first_token;
	}
	else
	{
		smash->last_token->next = malloc(sizeof(t_token));
		if (!smash->last_token->next)
			return (false);
		smash->last_token = smash->last_token->next;
	}
	smash->last_token->first_variable = NULL;
	smash->last_token->last_variable = NULL;
	smash->last_token->value = NULL;
	return (get_token_value(smash, start, len, type));
}

static bool	get_token_value(t_smash *smash,
	int start, int len, t_token_type type)
{
	if (type == SINGLE_QUOTE)
	{
		smash->last_token->value = ft_substr(smash->user_input, start, len);
		if (!smash->last_token->value)
			return (false);
	}
	else if (type == LITERAL || type == DOUBLE_QUOTE)
		if (!expand_variables(smash, start, len))
			return (false);
	smash->last_token->type = type;
	smash->last_token->next = NULL;
	return (true);
}

static bool	expand_variables(t_smash *smash, int start, int len)
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
			if (!get_variable(smash, iter))
				return (false);
			new_len -= smash->last_token->last_variable->key_len;
			new_len += smash->last_token->last_variable->value_len;
		}
		iter++;
	}
	smash->last_token->value = malloc((new_len + 1) * sizeof(char));
	if (!smash->last_token->value)
		return (false);
	copy_variables(smash, start, len);
	return (true);
}

static void	copy_variables(t_smash *smash, int start, int len)
{
	int		user_iter;
	int		iter;
	int		val_iter;
	t_var	*var_iter;

	user_iter = start;
	iter = 0;
	var_iter = smash->last_token->first_variable;
	while (user_iter < start + len)
	{
		while (var_iter && !var_iter->valid_name)
			var_iter = var_iter->next;
		if (var_iter && user_iter == var_iter->pos)
		{
			val_iter = 0;
			while (val_iter < var_iter->value_len)
				smash->last_token->value[iter++] = var_iter->value[val_iter++];
			user_iter += var_iter->key_len;
			var_iter = var_iter->next;
		}
		else
			smash->last_token->value[iter++] = smash->user_input[user_iter++];
	}
	smash->last_token->value[iter] = 0;
}
