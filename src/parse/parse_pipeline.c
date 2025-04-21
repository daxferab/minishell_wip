#include "minishell.h"

static t_pipeline	*new_pipeline(t_token *current);
static int			get_cmd_num(t_token *current);
static void			add_redirection(t_pipeline *pipelst, t_token **current);
static void			pipe_add_back(t_pipeline *new, t_pipeline **pipelst);

void	parse_pipeline(t_smash *smash)
{
	t_pipeline	*pipelst;
	t_token		*current;
	t_pipeline	*new;

	pipelst = NULL;
	current = smash->first_token;
	while (current)
	{
		new = new_pipeline(current); //TODO: protect
		pipe_add_back(new, &pipelst);
		while (current && current->type != PIPE)
			current = current->next;
		if (current && current->type == PIPE)
			current = current->next;
	}
	smash->first_pipeline = pipelst;
}

static t_pipeline	*new_pipeline(t_token *current)
{
	int			cmd_num;
	int			i;
	t_pipeline	*new_pipeline;

	cmd_num = get_cmd_num(current);
	i = 0;
	new_pipeline = malloc(sizeof(t_pipeline)); //TODO: protect
	new_pipeline->cmd = malloc(sizeof(char *) * (cmd_num + 1)); //TODO: protect
	new_pipeline->redir_lst = NULL;
	while (current && current->type != PIPE)
	{
		if (is_redirection(current->type))
			add_redirection(new_pipeline, &current);
		else
		{
			new_pipeline->cmd[i++] = current->value;
			current = current->next;
		}
	}
	new_pipeline->cmd[i] = NULL;
	new_pipeline->next = NULL;
	new_pipeline->fd_in = STDIN_FILENO;
	new_pipeline->fd_out = STDOUT_FILENO;
	return (new_pipeline);
}

static int	get_cmd_num(t_token *current)
{
	int		cmd_num;
	t_token	*before;

	cmd_num = 0;
	before = NULL;
	while (current && current->type != PIPE)
	{
		if (is_word(current->type) && (!before || !is_redirection(before->type)))
			cmd_num++;
		before = current;
		current = current->next;
	}
	return (cmd_num);
}

static void	add_redirection(t_pipeline *pipelst, t_token **current)
{
	t_redir	*redir;
	t_redir	*aux;

	redir = malloc(sizeof(t_redir)); // TODO: Proteger malloc
	redir->type = (*current)->type;
	redir->value = (*current)->next->value;
	redir->fd = -1;
	redir->next = NULL;
	if (!pipelst->redir_lst)
		pipelst->redir_lst = redir;
	else
	{
		aux = pipelst->redir_lst;
		while (aux->next)
			aux = aux->next;
		aux->next = redir;
	}
	*current = (*current)->next->next;
}

static void	pipe_add_back(t_pipeline *new, t_pipeline **pipelst)
{
	t_pipeline	*last;

	if (!*pipelst)
	{
		*pipelst = new;
		return ;
	}
	last = *pipelst;
	while (last->next)
		last = last->next;
	last->next = new;
}
