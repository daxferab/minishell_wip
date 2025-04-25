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

char	**get_env_path(t_smash *smash)
{
	char	*env_path;
	char	**split;
	char	*substr;

	env_path = get_value(smash->envp, "PATH");
	if (!env_path)
		return (NULL);
	substr = ft_substr(env_path, 5, ft_strlen(env_path) - 5);
	if (!substr)
		return (NULL);
	split = ft_split(substr, ':');
	free(substr);
	return (split);
}

void	execute_command(t_smash *smash, t_pipeline *pipeline)
{
	char	**path;
	char	*command;

	path = get_env_path(smash);
	get_command(path, pipeline->cmd[0], &command);
	execve(command, pipeline->cmd, NULL);
	//TODO free stuff
}

void	child(t_smash *smash, t_pipeline *pipeline)
{
	if (!execute_builtins(smash, pipeline))
	{
		execute_command(smash, pipeline);
		ft_printf_fd(STDERR_FILENO, "not a builtin: %s\n", pipeline->cmd[0]);
	}
	clear_input(smash);
	free_smash(*smash);
	close(smash->fd_stdin);
	close(smash->fd_stdout);
	//TODO close all other fds from all pipelines
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
	wait_children(smash, pid);
}
