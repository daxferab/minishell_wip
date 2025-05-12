#include "minishell.h"

static void	prompt(t_smash *smash);

bool	parse_line(t_smash *smash)
{
	prompt(smash);
	if (!smash->user_input || !smash->user_input[0])
		return (true);
	add_history_entry(smash);
	if (!tokenize(smash) || !expand_variables(smash) || !remove_quotes(smash))
	{
		ft_putstr_fd("Malloc error\n", 2);
		clear_input(smash);
		free_smash(*smash);
		exit(1);
	}
	if (!syntax(smash))
		return (false);
	if (!parse_pipeline(smash))
	{
		ft_putstr_fd("Malloc error\n", 2);
		clear_input(smash);
		free_smash(*smash);
		exit(1);
	}
	return (true);
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
