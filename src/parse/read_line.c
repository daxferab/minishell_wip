#include "minishell.h"

void	read_line(t_smash *smash)
{
	smash->user_input = readline("\e[1;35mSMASH -> \e[0m");
	if (!smash->user_input)
		return ;
	debug_string(*smash, "line", smash->user_input);
	if (ft_strlen(smash->user_input) > 0)
		add_history(smash->user_input);
}
