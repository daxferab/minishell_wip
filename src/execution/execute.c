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
	if (smash->first_pipeline->next)
		return (false);
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
	else if (ft_str_equals(pipeline->cmd[0], "exit")) //TODO: return status
		smash->exit_status = cmd_exit(smash, pipeline->cmd);
	else
		return (false);
	return (true);
}

void	execute(t_smash *smash)
{
	t_pipeline	*pipeline;
	int			i;
	int			j;

	open_pipes(smash);
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
		//TODO dup stdin stdout
		if (!execute_builtins(smash, pipeline))
			{
			/* 	fork();
				if (children)
					input_handler(smash, pipeline->cmd);*/
			}
		//TODO dup stdin stdout
		pipeline = pipeline->next;
		i++;
	}
}
