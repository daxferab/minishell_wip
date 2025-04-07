#include "minishell.h"

static int	get_cmd_num(t_token *current);
static void	new_pipeline(t_pipelines *pipelst, t_token *current);

void	parse_pipeline(t_smash *smash)
{
	int			cmd_num;
	int			i;
	t_pipelines	*pipelst;
	t_token		*current;

	pipelst = NULL;
	current = smash->first_token;
	while (current)
	{
		new_pipeline(pipelst, current);
		while (current && current->type != PIPE)
			current = current->next;
	}
	smash->first_redir = pipelst;
}

static void	new_pipeline(t_pipelines *pipelst, t_token *current)
{
	int			cmd_num;
	int			i;
	t_pipelines	*new_pipeline;

	cmd_num = get_cmd_num(current);
	i = 0;
	new_pipeline = malloc(sizeof(t_pipelines));
	new_pipeline->cmd = malloc(sizeof(char *) * (cmd_num + 1)); //TODO: protect
	while (current && current->type != PIPE)
	{
		if (is_redirection(current->type))
		{
			add_redirection(new_pipeline, current); //TODO: create this function
			current = current->next;
		}
		else
			new_pipeline->cmd[i++] = current->value;
		current = current->next;
	}
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
