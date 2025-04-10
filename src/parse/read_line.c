#include "minishell.h"

void	read_line(t_smash *smash)
{
	smash->user_input = readline("\e[1;35mSMASH -> \e[0m");
	if (!smash->user_input)
		return ;
	add_history_entry(smash);
	tokenize(smash);//TODO error
	expand_variables(smash);//TODO error
	remove_quotes(smash);//TODO error
	debug_tokens(smash);
	if (!syntax(smash))
		ft_printf_fd(STDERR_FILENO, "smash: syntax error\n");
	parse_pipeline(smash);
}
