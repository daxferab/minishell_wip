#include "minishell.h"

// static void	copy_variables(t_smash *smash, int start, int len);
static bool	expand_token(t_smash *smash, t_token *token);

bool	expand_variables(t_smash *smash)
{
	t_token			*iter;
	t_token_type	last_type;

	iter = smash->first_token;
	last_type = -1;
	while (iter)
	{
		if (iter->type == LITERAL && last_type != HEREDOC)
			expand_token(smash, iter);
		last_type = iter->type;
		iter = iter->next;
	}
	return (true);
}

static bool	expand_token(t_smash *smash, t_token *token)
{
	int				iter;
	t_token_type	type;

	(void) smash; //TODO remove
	iter = 0;
	type = LITERAL;
	while (token->value[iter])
	{
		mutate(&type, token->value[iter]);
		if (token->value[iter] == '$'
			&& !(iter > 0 && token->value[iter - 1] == '$')
			&& (type == LITERAL || type == DOUBLE_QUOTE))
			ft_printf("TODO: expand dollar at %i of %s\n", iter, token->value);
		iter++;
	}
	return (true);
}

// static bool	expand_variables(t_smash *smash, int start, int len)
// {
// 	int	iter;
// 	int	new_len;

// 	iter = start;
// 	new_len = len;
// 	while (iter < start + len)
// 	{
// 		if (smash->user_input[iter] == '$'
// 			&& !(iter > 0 && smash->user_input[iter - 1] == '$'))
// 		{
// 			if (!get_variable(smash, iter))
// 				return (false);
// 			new_len -= smash->last_token->last_variable->key_len;
// 			new_len += smash->last_token->last_variable->value_len;
// 		}
// 		iter++;
// 	}
// 	smash->last_token->value = malloc((new_len + 1) * sizeof(char));
// 	if (!smash->last_token->value)
// 		return (false);
// 	copy_variables(smash, start, len);
// 	return (true);
// }

// static void	copy_variables(t_smash *smash, int start, int len)
// {
// 	int		user_iter;
// 	int		iter;
// 	int		val_iter;
// 	t_var	*var_iter;

// 	user_iter = start;
// 	iter = 0;
// 	var_iter = smash->last_token->first_variable;
// 	while (user_iter < start + len)
// 	{
// 		while (var_iter && !var_iter->valid_name)
// 			var_iter = var_iter->next;
// 		if (var_iter && user_iter == var_iter->pos)
// 		{
// 			val_iter = 0;
// 			while (val_iter < var_iter->value_len)
// 				smash->last_token->value[iter++] = var_iter->value[val_iter++];
// 			user_iter += var_iter->key_len;
// 			var_iter = var_iter->next;
// 		}
// 		else
// 			smash->last_token->value[iter++] = smash->user_input[user_iter++];
// 	}
// 	smash->last_token->value[iter] = 0;
// }
