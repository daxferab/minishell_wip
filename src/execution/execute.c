#include "minishell.h"

void	execute(t_smash *smash)
{
	t_pipeline	*pipeline;
	int			i;
	int			j;

	handle_redirections(smash);
	pipeline = smash->first_pipeline;
	i = 0;
	while (pipeline)
	{
		debug_int(smash, "Pipeline", i);
		debug_int(smash, " fd_in", pipeline->fd_in);
		debug_int(smash, " fd_out", pipeline->fd_out);
		debug_string(smash, " cmd", "");
		j = 0;
		while (pipeline->cmd[j])
			debug_string(smash, "    ", pipeline->cmd[j++]);
		input_handler(smash, pipeline->cmd);
		pipeline = pipeline->next;
		i++;
	}
}
