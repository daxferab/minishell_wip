#include "minishell.h"

bool	valid_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
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
	i = pos + 1;
	smash->last_token->last_variable->valid_name = false;
	if (!ft_isalpha(smash->user_input[i]) && smash->user_input[i] != '_' && smash->user_input[i] != '?')
		return ;
	smash->last_token->last_variable->valid_name = true;
	smash->last_token->last_variable->pos = pos;
	if (smash->user_input[i] == '?')
	{
		smash->last_token->last_variable->value = ft_itoa(smash->exit_status); //TODO error malloc
		smash->last_token->last_variable->key_len = 2;
		smash->last_token->last_variable->value_len = ft_strlen(smash->last_token->last_variable->value);
		return ;
	}
	while (smash->user_input[i] && valid_char(smash->user_input[i]))
		i++;
	key = ft_substr(smash->user_input, pos + 1, i - pos - 1); //TODO error malloc
	smash->last_token->last_variable->key_len = i - pos;
	smash->last_token->last_variable->value = get_value(smash->envp, key);
	free(key);
	smash->last_token->last_variable->value_len = ft_strlen(smash->last_token->last_variable->value);
}
