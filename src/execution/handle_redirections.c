#include "minishell.h"

void	handle_redirections(t_smash *smash)
{
	t_pipeline	*pipeline;
	t_redir		*redir;

	pipeline = smash->first_pipeline;
	while (pipeline)
	{
		redir = pipeline->redir_lst;
		while (redir)
		{
			debug_int(smash, "Redir type", redir->type);
			debug_string(smash, "Redir value", redir->value);
			redir = redir->next;
		}
		pipeline = pipeline->next;
	}
}
