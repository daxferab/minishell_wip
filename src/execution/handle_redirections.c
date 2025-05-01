#include "minishell.h"

static void	open_heredoc(t_smash *smash, t_redir *redir);
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
			open_heredoc(smash, redir);
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

//TODO for now, heredoc closes with Ctrl+d
static void	open_heredoc(t_smash *smash, t_redir *redir)
{
	int		fds[2];
	char	*line;
	bool	end;
	t_token	*token;

	if (redir->type != HEREDOC)
		return ;
	end = false;
	pipe(fds);//TODO protect
	while (!end)
	{
		token = ft_calloc(1, sizeof(t_token));//TODO protect
		token->value = readline("> ");
		if (!token->value || ft_str_equals(redir->value, token->value))
			end = true;
		if (!end)
		{
			expand_token(smash, token);//TODO protect
			line = ft_strjoin(token->value, "\n");//TODO protect
			ft_printf_fd(fds[PIPE_WRITE], "%s", line);
			free(line);
		}
		clear_tokens(token);
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
