#include "minishell.h"

static void	execute_child(t_smash *smash, t_pipeline *pipeline);
static void	close_unused_fds(t_smash *smash, t_pipeline *pipeline);
static void	backup_std_fds(t_smash *smash, t_pipeline *pipeline);
static void	restore_std_fds(t_smash *smash);

void	execute_command(t_smash *smash, t_pipeline *pipeline, pid_t *pid)
{
	if (pipeline->fd_in < 0 || pipeline->fd_out < 0 || !pipeline->cmd[0])
		return ;
	backup_std_fds(smash, pipeline);
	if (smash->first_pipeline->next || !execute_builtins(smash, pipeline))
	{
		*pid = fork();
		// if (pid == -1)
		// 	;//TODO protect fork
		if (*pid == 0)
			execute_child(smash, pipeline);
	}
	restore_std_fds(smash);
}

static void	execute_child(t_smash *smash, t_pipeline *pipeline)
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

static void	backup_std_fds(t_smash *smash, t_pipeline *pipeline)
{
	smash->fd_stdin = -1;
	smash->fd_stdout = -1;
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
}

static void	restore_std_fds(t_smash *smash)
{
	if (smash->fd_stdin != -1)
	{
		dup2(smash->fd_stdin, STDIN_FILENO); //TODO protect dup2
		close(smash->fd_stdin);
	}
	if (smash->fd_stdout != -1)
	{
		dup2(smash->fd_stdout, STDOUT_FILENO); //TODO protect dup2
		close(smash->fd_stdout);
	}
}
