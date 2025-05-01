#include "minishell.h"

static void	close_unused_fds(t_smash *smash, t_pipeline *pipeline);

void	execute_child(t_smash *smash, t_pipeline *pipeline)
{
	close_unused_fds(smash, pipeline);
	if (!execute_builtins(smash, pipeline))
		execute_external(smash, pipeline);
	close(pipeline->fd_in);
	close(pipeline->fd_out);
	clear_input(smash);
	free_smash(*smash);
	exit(smash->exit_status);
}

static void	close_unused_fds(t_smash *smash, t_pipeline *pipeline)
{
	t_pipeline	*iter;

	if (smash->fd_stdin != -1)
		close(smash->fd_stdin);
	if (smash->fd_stdout != -1)
		close(smash->fd_stdout);
	iter = smash->first_pipeline;
	while (iter)
	{
		if (iter != pipeline)
		{
			if (iter->fd_in != STDIN_FILENO && iter->fd_in != -1)
				close(iter->fd_in);
			if (iter->fd_out != STDOUT_FILENO && iter->fd_out != -1)
				close(iter->fd_out);
		}
		iter = iter->next;
	}
}
