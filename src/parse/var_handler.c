#include "minishell.h"

static bool	variable_name_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static bool	variable_name_valid_first_char(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

//TODO protect NULL
void	get_var(t_smash *smash, int pos)
{
	int		i;
	char	*key;

	if (!smash->last_token->first_variable)
	{
		smash->last_token->first_variable = malloc(sizeof(t_var));
		smash->last_token->last_variable = smash->last_token->first_variable;
	}
	else
	{
		smash->last_token->last_variable->next = malloc(sizeof(t_var));
		smash->last_token->last_variable = smash->last_token->last_variable->next;
	}
	smash->last_token->last_variable->next = NULL;
	smash->last_token->last_variable->valid_name = false;
	smash->last_token->last_variable->pos = pos;
	smash->last_token->last_variable->key_len = 0;
	smash->last_token->last_variable->value_len = 0;
	smash->last_token->last_variable->value = NULL;
	i = pos + 1;
	if (!variable_name_valid_first_char(smash->user_input[i]))
		return ;
	smash->last_token->last_variable->valid_name = true;
	if (smash->user_input[i] == '?')
	{
		smash->last_token->last_variable->value = ft_itoa(smash->exit_status); //TODO error malloc
		smash->last_token->last_variable->key_len = 2;
		smash->last_token->last_variable->value_len = ft_strlen(smash->last_token->last_variable->value);
		return ;
	}
	while (variable_name_valid_char(smash->user_input[i]))
		i++;
	smash->last_token->last_variable->key_len = i - pos;
	key = ft_substr(smash->user_input, pos + 1, i - pos - 1); //TODO error malloc
	smash->last_token->last_variable->value = get_value(smash->envp, key);
	free(key);
	smash->last_token->last_variable->value_len = ft_strlen(smash->last_token->last_variable->value);
}
