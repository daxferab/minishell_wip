#include "minishell.h"

static bool	open_pipes(t_pipeline *pipeline);
static void	wait_children(t_smash *smash, pid_t last_child);

void	execute(t_smash *smash)
{
	t_pipeline	*pipeline;
	pid_t		pid;

	pid = INIT_PID;
	if (!open_pipes(smash->first_pipeline) || !handle_redirections(smash))
	{
		clear_input(smash);
		ft_printf_fd(2, "Error in execute\n");//TODO protect
		return ;
	}
	{
		pipeline = smash->first_pipeline;
		while (pipeline)
		{
			execute_command(smash, pipeline, &pid);
			pipeline = pipeline->next;
		}
	}
	clear_input(smash);
	wait_children(smash, pid);
}

static bool	open_pipes(t_pipeline *pipeline)
{
	int			fds[2];

	while (pipeline->next)
	{
		if (pipe(fds) == -1)
			return (false);
		pipeline->fd_out = fds[PIPE_WRITE];
		pipeline->next->fd_in = fds[PIPE_READ];
		pipeline = pipeline->next;
	}
	return (true);
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
