#include "minishell.h"

static void	open_heredoc(t_redir *redir);
static void	open_fd(t_pipeline *pipeline, t_redir *redir);

void	handle_redirections(t_smash *smash)
{
	t_pipeline	*pipeline;
	t_redir		*redir;

	pipeline = smash->first_pipeline;
	while (pipeline)
	{
		redir = pipeline->redir_lst;
		while (redir)
		{
			open_heredoc(redir);
			redir = redir->next;
		}
		pipeline = pipeline->next;
	}
	pipeline = smash->first_pipeline;
	while (pipeline)
	{
		redir = pipeline->redir_lst;
		while (redir)
		{
			open_fd(pipeline, redir);
			redir = redir->next;
		}
		pipeline = pipeline->next;
	}
}

static void	open_heredoc(t_redir *redir)
{
	int		fds[2];
	char	*line;
	bool	end;

	if (redir->type != HEREDOC)
		return ;
	end = false;
	pipe(fds);//TODO protect
	while (!end)
	{
		line = readline("> ");
		//TODO for now, heredoc closes with Ctrl+d
		if (!line || ft_str_equals(redir->value, line))
			end = true;
		if (!end)
			ft_printf_fd(fds[PIPE_WRITE], "%s", line);
		free(line);
	}
	close(fds[PIPE_WRITE]);
	redir->fd = fds[PIPE_READ];
}

static void	open_fd(t_pipeline *pipeline, t_redir *redir)
{
	errno = 0;
	if ((pipeline->fd_in == -1 || pipeline->fd_out == -1) && redir->fd != -1)
		close(redir->fd);
	if (pipeline->fd_in == -1 || pipeline->fd_out == -1)
		return ;
	if (redir->type == INPUT)
		redir->fd = open(redir->value, O_RDONLY);
	else if (redir->type == OUTPUT)
		redir->fd = open(redir->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (redir->type == APPEND)
		redir->fd = open(redir->value, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (redir->fd < 0)
		ft_printf("smash: %s: %s\n", redir->value, strerror(errno));
	if ((redir->type == INPUT || redir->type == HEREDOC)
		&& pipeline->fd_in != STDIN_FILENO)
		close(pipeline->fd_in);
	if (redir->type == INPUT || redir->type == HEREDOC)
		pipeline->fd_in = redir->fd;
	if ((redir->type == OUTPUT || redir->type == APPEND)
		&& pipeline->fd_out != STDOUT_FILENO)
		close(pipeline->fd_out);
	if (redir->type == OUTPUT || redir->type == APPEND)
		pipeline->fd_out = redir->fd;
	errno = 0;
}
