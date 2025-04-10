#include "minishell.h"

static void	clear_vars(t_token *token);
static void	free_redir(t_redir *redir);

void	clear_input(t_smash *smash)
{
	t_token	*iter;
	t_token	*next;

	iter = smash->first_token;
	while (iter)
	{
		next = iter->next;
		clear_vars(iter);
		free(iter->value);
		free(iter);
		iter = next;
	}
	smash->first_token = NULL;
	smash->last_token = NULL;
	free(smash->user_input);
}

static void	clear_vars(t_token *token)
{
	t_var	*iter;
	t_var	*next;

	iter = token->first_variable;
	while (iter)
	{
		next = iter->next;
		free(iter->value);
		free(iter);
		iter = next;
	}
}

void	clear_pipeline(t_smash *smash)
{
	t_pipeline	*tmp;

	while (smash->first_pipeline)
	{

		tmp = smash->first_pipeline;
		ft_free_double_pointer(tmp->cmd);
		free_redir(tmp->redir_lst);
		free(tmp);
		smash->first_pipeline = smash->first_pipeline->next;
	}
}

static void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		free(tmp->value);
		free(tmp);
		redir = redir->next;
	}
}
