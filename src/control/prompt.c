#include "minishell.h"

char	*prompt(t_smash *smash, bool in_heredoc)
{
	if (smash->debug_mode)
	{
		if (in_heredoc)
			ft_printf(HEREDOC_PROMPT);
		else
			ft_printf(PROMPT);
		return (ft_get_next_line_no_nl(STDIN_FILENO));
	}
	else if (in_heredoc)
		return (readline(HEREDOC_PROMPT));
	return (readline(PROMPT));
}
