#include "minishell.h"

static bool	open_heredoc(t_smash *smash, t_redir *redir);
static void	open_fd(t_pipeline *pipeline, t_redir *redir);

bool	handle_redirections(t_smash *smash)
{
	t_pipeline	*pipeline;
	t_redir		*redir;

	pipeline = smash->first_pipeline;
	while (pipeline)
	{
		redir = pipeline->redir_lst;
		while (redir)
		{
			if (!open_heredoc(smash, redir))
			{
				ft_printf_fd(2, "ERROR opening heredocs\n");
				return (false);
			}
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
	return (true);
}

//TODO for now, heredoc closes with Ctrl+d
static bool	open_heredoc(t_smash *smash, t_redir *redir)
{
	int		fds[2];
	t_token	*head;
	t_token	*iter;

	if (redir->type != HEREDOC)
		return (true);
	head = ft_calloc(1, sizeof(t_token));
	if (!head)
		return (false);
	if (pipe(fds) == -1)
	{
		free(head);
		return (false);
	}
	iter = head;
	while (true)
	{
		iter->value = prompt(smash, true);
		if (!iter->value || ft_str_equals(redir->value, iter->value))
			break ;
		if (!expand_token(smash, iter, true))
		{
			clear_tokens(head);
			close(fds[0]);
			close(fds[1]);
			return (false);
		}
		ft_printf_fd(fds[PIPE_WRITE], "%s\n", iter->value);
		iter->next = ft_calloc(1, sizeof(t_token));
		if (!iter->next)
		{
			clear_tokens(head);
			close(fds[0]);
			close(fds[1]);
			return (false);
		}
		iter = iter->next;
	}
	clear_tokens(head);
	close(fds[PIPE_WRITE]);
	redir->fd = fds[PIPE_READ];
	return (true);
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
