#include "minishell.h"

static int	open_heredoc(char *delim);

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
			if (redir->type == HEREDOC)
				redir->fd = open_heredoc(redir->value);
			redir = redir->next;
		}
		pipeline = pipeline->next;
	}
}

static int	open_heredoc(char *delim)
{
	int		fds[2];
	char	*line;
	bool	end;

	end = false;
	pipe(fds);//TODO protect
	while (!end)
	{
		//line = readline("> ");
		ft_printf("> ");
		line = ft_get_next_line_no_nl(STDIN_FILENO);
		//TODO for now, heredoc closes with Ctrl+d
		if (!line || ft_str_equals(delim, line))
			end = true;
		if (!end)
			ft_printf_fd(fds[PIPE_WRITE], "%s", line);
		free(line);
	}
	close(fds[PIPE_WRITE]);
	return (fds[PIPE_READ]);
}
