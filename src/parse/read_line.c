#include "minishell.h"

void	quotes(t_smash *smash)
{
	int	iter;
	int	mode;//0 normal 1 ' 2 "

	mode = 0;
	iter = 0;
	while (smash->user_input[iter])
	{
		if (mode == 0 && smash->user_input[iter] == '\'')
		{
			debug_int(*smash, "start ' pos", iter);
			mode = 1;
		}
		else if (mode == 0 && smash->user_input[iter] == '"')
		{
			debug_int(*smash, "start \" pos", iter);
			mode = 2;
		}
		else if (mode == 1 && smash->user_input[iter] == '\'')
		{
			debug_int(*smash, "end ' pos", iter);
			mode = 0;
		}
		else if (mode == 2 && smash->user_input[iter] == '"')
		{
			debug_int(*smash, "end \" pos", iter);
			mode = 0;
		}
		iter++;
	}
	if (mode == 1)
		debug_string(*smash, "unclosed quotes", "'");
	if (mode == 2)
		debug_string(*smash, "unclosed quotes", "\"");
}

void	read_line(t_smash *smash)
{
	smash->user_input = readline("\e[1;35mSMASH -> \e[0m");
	if (!smash->user_input)
		return ;
	//debug_string(*smash, "line", smash->user_input);
	/* iter = 0;
	while (smash->user_input[iter])
	{
		if (smash->user_input[iter] == '\'')
			debug_int(*smash, "' pos", iter);
		if (smash->user_input[iter] == '"')
			debug_int(*smash, "\" pos", iter);
		if (smash->user_input[iter] == '|')
			debug_int(*smash, "| pos", iter);
		if (smash->user_input[iter] == '$')
			debug_int(*smash, "$ pos", iter);
		if (smash->user_input[iter] == '<')
			debug_int(*smash, "< pos", iter);
		if (smash->user_input[iter] == '>')
			debug_int(*smash, "> pos", iter);
		iter++;
	} */
	quotes(smash);
	if (ft_strlen(smash->user_input) > 0)
		add_history(smash->user_input);
}
