#include "minishell.h"

void	open_pipes(t_smash *smash);
void	wait_children(t_smash *smash, pid_t last_child);

void	execute(t_smash *smash)
{
	t_pipeline	*pipeline;
	pid_t		pid;

	pid = -1;
	open_pipes(smash);
	handle_redirections(smash);
	pipeline = smash->first_pipeline;
	smash->fd_stdin = -1;
	smash->fd_stdout = -1;
	while (pipeline)
	{
		if (pipeline->fd_in < 0 || pipeline->fd_out < 0 || !pipeline->cmd[0])
		{
			pipeline = pipeline->next;
			continue ;
		}
		if (pipeline->fd_in != STDIN_FILENO)
		{
			smash->fd_stdin = dup(STDIN_FILENO); //TODO protect dup
			dup2(pipeline->fd_in, STDIN_FILENO); //TODO protect dup2
			close(pipeline->fd_in);
		}
		if (pipeline->fd_out != STDOUT_FILENO)
		{
			smash->fd_stdout = dup(STDOUT_FILENO); //TODO protect dup
			dup2(pipeline->fd_out, STDOUT_FILENO); //TODO protect dup2
			close(pipeline->fd_out);
		}
		if (smash->first_pipeline->next || !execute_builtins(smash, pipeline))
		{
			pid = fork();
			// if (pid == -1)
			// 	;//TODO protect fork
			if (pid == 0)
				execute_child(smash, pipeline);
		}
		if (smash->fd_stdin != -1)
		{
			dup2(smash->fd_stdin, STDIN_FILENO); //TODO protect dup2
			close(smash->fd_stdin);
			smash->fd_stdin = -1;
		}
		if (smash->fd_stdout != -1)
		{
			dup2(smash->fd_stdout, STDOUT_FILENO); //TODO protect dup2
			close(smash->fd_stdout);
			smash->fd_stdout = -1;
		}
		pipeline = pipeline->next;
	}
	clear_input(smash);
	wait_children(smash, pid);
}

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

void	wait_children(t_smash *smash, pid_t last_child)
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
