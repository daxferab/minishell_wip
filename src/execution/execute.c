#include "minishell.h"

static void	open_pipes(t_smash *smash);
static void	wait_children(t_smash *smash, pid_t last_child);

void	execute(t_smash *smash)
{
	t_pipeline	*pipeline;
	pid_t		pid;

	pid = INIT_PID;
	open_pipes(smash);
	handle_redirections(smash);
	pipeline = smash->first_pipeline;
	while (pipeline)
	{
		execute_command(smash, pipeline, &pid);
		pipeline = pipeline->next;
	}
	clear_input(smash);
	wait_children(smash, pid);
}

static void	open_pipes(t_smash *smash)
{
	t_pipeline	*iter;
	int			fds[2];

	iter = smash->first_pipeline;
	while (iter->next)
	{
		pipe(fds);//TODO protect
		iter->fd_out = fds[PIPE_WRITE];
		iter->next->fd_in = fds[PIPE_READ];
		iter = iter->next;
	}
}

static void	wait_children(t_smash *smash, pid_t last_child)
{
	int		status;
	pid_t	pid;

	pid = 0;
	status = -1;
	while (pid != -1)
	{
		pid = wait(&status);
		if (pid == last_child)
			smash->exit_status = WEXITSTATUS(status);
	}
}
