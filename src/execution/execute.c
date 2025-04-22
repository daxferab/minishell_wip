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

bool	execute_builtins(t_smash *smash, t_pipeline *pipeline)
{
	// if (smash->first_pipeline->next)
		// return (false);
	if (ft_str_equals(pipeline->cmd[0], "env"))
		smash->exit_status = cmd_env(*smash, pipeline->cmd);
	else if (ft_str_equals(pipeline->cmd[0], "pwd"))
		smash->exit_status = cmd_pwd(smash, pipeline->cmd);
	else if (ft_str_equals(pipeline->cmd[0], "unset"))
		smash->exit_status = cmd_unset(smash, pipeline->cmd);
	else if (ft_str_equals(pipeline->cmd[0], "export"))
		smash->exit_status = cmd_export(smash, pipeline->cmd);
	else if (ft_str_equals(pipeline->cmd[0], "echo"))
		smash->exit_status = cmd_echo(pipeline->cmd);
	else if (ft_str_equals(pipeline->cmd[0], "cd"))
		smash->exit_status = cmd_cd(smash, pipeline->cmd);
	else if (ft_str_equals(pipeline->cmd[0], "exit"))
		smash->exit_status = cmd_exit(smash, pipeline->cmd);
	else
		return (false);
	return (true);
}

void	execute(t_smash *smash)
{
	t_pipeline	*pipeline;
	int			fd_stdin;
	int			fd_stdout;
	pid_t		pid;

	open_pipes(smash);
	handle_redirections(smash);
	pipeline = smash->first_pipeline;
	while (pipeline)
	{
		fd_stdin = dup(STDIN_FILENO); //TODO protect dup
		fd_stdout = dup(STDOUT_FILENO); //TODO protect dup
		dup2(pipeline->fd_in, STDIN_FILENO); //TODO protect dup2
		dup2(pipeline->fd_out, STDOUT_FILENO); //TODO protect dup2
		if (smash->first_pipeline->next || !execute_builtins(smash, pipeline))
		{
			pid = fork();
			if (pid == -1)
				;//TODO protect fork
			if (pid == 0)
			{
				if (!execute_builtins(smash, pipeline))
					ft_printf_fd(STDERR_FILENO, "not a builtin: %s\n", pipeline->cmd[0]);
				clear_input(smash);
				free_smash(*smash);
				close(fd_stdin);
				close(fd_stdout);
				//TODO close all other fds from all pipelines
				exit(smash->exit_status);
			}
		}
		dup2(fd_stdin, STDIN_FILENO); //TODO protect dup2
		dup2(fd_stdout, STDOUT_FILENO); //TODO protect dup2
		close(fd_stdin);
		close(fd_stdout);
		pipeline = pipeline->next;
	}
}
