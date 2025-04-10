#include "minishell.h"

static void	clear_tokens(t_smash *smash);
static void	clear_vars(t_token *token);
static void	clear_pipelines(t_smash *smash);
static void	clear_redirs(t_pipeline *pipeline);

void	clear_input(t_smash *smash)
{
	clear_tokens(smash);
	clear_pipelines(smash);
	free(smash->user_input);
}

static void	clear_tokens(t_smash *smash)
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

static void	clear_pipelines(t_smash *smash)
{
	t_pipeline	*iter;
	t_pipeline	*next;

	iter = smash->first_pipeline;
	while (iter)
	{
		next = iter->next;
		clear_redirs(iter);
		free(iter->cmd);
		free(iter);
		iter = next;
	}
}

static void	clear_redirs(t_pipeline *pipeline)
{
	t_redir	*iter;
	t_redir	*next;

	iter = pipeline->redir_lst;
	while (iter)
	{
		next = iter->next;
		free(iter);
		iter = next;
	}
}
