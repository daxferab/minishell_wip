#include "minishell.h"

static void	prompt(t_smash *smash);

void	parse_line(t_smash *smash)
{
	prompt(smash);
	if (!smash->user_input || !smash->user_input[0])
		return ;
	add_history_entry(smash);
	tokenize(smash);//TODO error
	expand_variables(smash);//TODO error
	remove_quotes(smash);//TODO error
	//debug_tokens(smash);
	if (!syntax(smash))
		ft_printf_fd(STDERR_FILENO, "smash: syntax error\n");
	parse_pipeline(smash);
}

static void	prompt(t_smash *smash)
{
	if (smash->debug_mode)
	{
		ft_printf("\e[1;38;5;99mSMASHD -> \e[0m");
		smash->user_input = ft_get_next_line_no_nl(STDIN_FILENO);
	}
	else
		smash->user_input = readline("\e[1;38;5;99mSMASH -> \e[0m");
}
