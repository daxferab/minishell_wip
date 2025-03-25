#include "minishell.h"

bool	valid_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

t_var	get_var(t_smash smash, char *input, int pos)
{
	int		i;
	t_var	var;
	char	*key;

	i = pos + 1;
	var.valid_name = false;
	if (!ft_isalpha(input[i]) && input[i] != '_' && input[i] != '?')
		return (var);
	var.valid_name = true;
	var.pos = pos;
	if (input[i] == '?')
	{
		var.value = ft_itoa(smash.exit_status);
		var.key_len = 2;
		var.value_len = ft_strlen(var.value);
		return (var);
	}
	while (input[i] && valid_char(input[i]))
		i++;
	key = ft_substr(input, pos + 1, i - pos - 1);
	var.key_len = i - pos - 1;
	var.value = get_value(smash.envp, key);
	free(key);
	return (var);
}
