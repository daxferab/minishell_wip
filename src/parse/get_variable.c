#include "minishell.h"

static bool		get_var_exit_status(t_smash *smash);
static bool		get_var_regular_variable(t_smash *smash, int pos);
static size_t	len(t_smash *smash, int pos);

//returns false if malloc fails
bool	get_variable(t_smash *smash, int pos)
{
	if (!smash->last_token->first_variable)
	{
		smash->last_token->first_variable = malloc(sizeof(t_var));
		smash->last_token->last_variable = smash->last_token->first_variable;
	}
	else
	{
		smash->last_token->last_variable->next = malloc(sizeof(t_var));
		smash->last_token->last_variable
			= smash->last_token->last_variable->next;
	}
	smash->last_token->last_variable->next = NULL;
	smash->last_token->last_variable->valid_name = false;
	smash->last_token->last_variable->pos = pos;
	smash->last_token->last_variable->value = NULL;
	smash->last_token->last_variable->key_len = 0;
	smash->last_token->last_variable->value_len = 0;
	if (smash->user_input[pos + 1] == '?')
		return (get_var_exit_status(smash));
	return (get_var_regular_variable(smash, pos));
}

static bool	get_var_exit_status(t_smash *smash)
{
	smash->last_token->last_variable->valid_name = false;
	smash->last_token->last_variable->value = ft_itoa(smash->exit_status);
	if (!smash->last_token->last_variable->value)
		return (false);
	smash->last_token->last_variable->key_len = 2;
	smash->last_token->last_variable->value_len
		= ft_strlen(smash->last_token->last_variable->value);
	return (true);
}

static bool	get_var_regular_variable(t_smash *smash, int pos)
{
	char	*key;
	char	*value;
	size_t	key_len;

	key_len = len(smash, pos + 1);
	if (key_len == 0)
		return (true);
	smash->last_token->last_variable->valid_name = true;
	smash->last_token->last_variable->key_len = key_len + 1;
	key = ft_substr(smash->user_input, pos + 1, key_len);
	if (!key)
		return (false);
	value = get_value(smash->envp, key);
	free(key);
	if (!value)
		return (true);
	smash->last_token->last_variable->value = ft_strdup(value);
	if (!smash->last_token->last_variable->value)
		return (false);
	smash->last_token->last_variable->value_len
		= ft_strlen(smash->last_token->last_variable->value);
	return (true);
}

static size_t	len(t_smash *smash, int pos)
{
	size_t	len;

	len = 0;
	if (!(ft_isalpha(smash->user_input[pos]) || smash->user_input[pos] == '_'))
		return (len);
	while (ft_isalnum(smash->user_input[pos]) || smash->user_input[pos] == '_')
	{
		pos++;
		len++;
	}
	return (len);
}
