#include "minishell.h"

void	open_pipes(t_smash *smash)
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

//TODO close all other fds from all pipelines
void	close_unused_fds(t_smash *smash, t_pipeline *pipeline)
{
	t_pipeline	*iter;

	close(smash->fd_stdin);
	close(smash->fd_stdout);
	iter = smash->first_pipeline;
	while (iter)
	{
		if(iter != pipeline)
		{
			if(iter->fd_in != STDIN_FILENO)
				close(iter->fd_in);
			if(iter->fd_out != STDOUT_FILENO)
				close(iter->fd_out);
		}
		iter = iter->next;
	}
}

void	child(t_smash *smash, t_pipeline *pipeline)
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

void	wait_children(t_smash *smash, pid_t last_child)
{
	int		status;
	pid_t	pid;

	pid = 0;
	while (pid != -1)
	{
		pid = wait(&status);
		if (pid == last_child)
			smash->exit_status = WEXITSTATUS(status);
	}
}

void	execute(t_smash *smash)
{
	t_pipeline	*pipeline;
	pid_t		pid;

	open_pipes(smash);
	handle_redirections(smash);
	pipeline = smash->first_pipeline;
	while (pipeline)
	{
		//TODO if error in fds, no execution
		smash->fd_stdin = dup(STDIN_FILENO); //TODO protect dup
		smash->fd_stdout = dup(STDOUT_FILENO); //TODO protect dup
		dup2(pipeline->fd_in, STDIN_FILENO); //TODO protect dup2
		dup2(pipeline->fd_out, STDOUT_FILENO); //TODO protect dup2
		if (smash->first_pipeline->next || !execute_builtins(smash, pipeline))
		{
			pid = fork();
			if (pid == -1)
				;//TODO protect fork
			if (pid == 0)
				child(smash, pipeline);
		}
		dup2(smash->fd_stdin, STDIN_FILENO); //TODO protect dup2
		dup2(smash->fd_stdout, STDOUT_FILENO); //TODO protect dup2
		close(smash->fd_stdin);
		close(smash->fd_stdout);
		pipeline = pipeline->next;
	}
	clear_input(smash);
	wait_children(smash, pid);
}
