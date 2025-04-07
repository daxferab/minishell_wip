#include "minishell.h"

static int	get_cmd_num(t_token *current);
static void	new_pipeline(t_pipeline *pipelst, t_token *current);

void	parse_pipeline(t_smash *smash)
{
	t_pipeline	*pipelst;
	t_token		*current;

	pipelst = NULL;
	current = smash->first_token;
	while (current)
	{
		new_pipeline(pipelst, current);
		while (current && current->type != PIPE)
			current = current->next;
		if  (current && current->type == PIPE)
			current = current->next;
	}
	smash->first_pipeline = pipelst;
	t_pipeline	*aux = pipelst;
	while (aux)
	{
		int i = 0;
		while (aux->cmd[i])
		{
			ft_printf("cmd[%d] = %s\n", i, aux->cmd[i]);
			i++;
		}
		aux = aux->next;
	}
}

static void	add_redirection(t_pipeline *pipelst, t_token *current)
{
	t_redir	*redir;
	t_redir	*aux;

	redir = malloc(sizeof(t_redir)); //TODO: protect
	redir->type = current->type;
	redir->next = NULL;
	redir->value = current->next->value;
	aux = pipelst->redir_lst;
	while (aux && aux->next)
		aux = aux->next;
	if (aux)
		aux->next = redir;
	else
		pipelst->redir_lst = redir;
}

static void	new_pipeline(t_pipeline *pipelst, t_token *current)
{
	int			cmd_num;
	int			i;
	t_pipeline	*new_pipeline;

	(void) pipelst;
	cmd_num = get_cmd_num(current);
	i = 0;
	new_pipeline = malloc(sizeof(t_pipeline)); //TODO: protect
	new_pipeline->cmd = malloc(sizeof(char *) * (cmd_num + 1)); //TODO: protect
	new_pipeline->redir_lst = NULL;
	while (current && current->type != PIPE)
	{
		if (is_redirection(current->type))
		{
			add_redirection(new_pipeline, current);
			current = current->next;
		}
		else
			new_pipeline->cmd[i++] = current->value;
		current = current->next;
	}
	new_pipeline->cmd[i] = NULL;
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
