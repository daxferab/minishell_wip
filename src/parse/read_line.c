#include "minishell.h"

void	read_line(t_smash *smash)
{
	smash->user_input = readline("\e[1;35mSMASH -> \e[0m");
	if (!smash->user_input || !smash->user_input[0])
		return ;
	add_history_entry(smash);
	tokenize(smash);
	if (!syntax(smash))
		ft_printf_fd(STDERR_FILENO, "smash: syntax error\n");
	parse_pipeline(smash);
}
