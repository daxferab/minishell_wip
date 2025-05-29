#include "minishell.h"

static void	clear_vars(t_var *var);
static void	clear_pipelines(t_pipeline *pipeline);
static void	clear_redirs(t_redir *redir);

void	clear_input(t_smash *smash)
{
	clear_tokens(smash->first_token);
	clear_pipelines(smash->first_pipeline);
	free(smash->user_input);
	smash->first_token = NULL;
	smash->last_token = NULL;
	smash->first_pipeline = NULL;
	smash->user_input = NULL;
}

//TODO refactor
void	free_token(t_token *token)
{
	clear_vars(token->first_variable);
	free(token->value);
	free(token);
}

void	clear_tokens(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		clear_vars(token->first_variable);
		free(token->value);
		free(token);
		token = next;
	}
}

static void	clear_vars(t_var *var)
{
	t_var	*next;

	while (var)
	{
		next = var->next;
		free(var->value);
		free(var);
		var = next;
	}
}

static void	clear_pipelines(t_pipeline *pipeline)
{
	t_pipeline	*next;

	while (pipeline)
	{
		next = pipeline->next;
		if (pipeline->fd_in != STDIN_FILENO && pipeline->fd_in != -1)
			close(pipeline->fd_in);
		if (pipeline->fd_out != STDOUT_FILENO && pipeline->fd_out != -1)
			close(pipeline->fd_out);
		clear_redirs(pipeline->redir_lst);
		free(pipeline->cmd);
		free(pipeline);
		pipeline = next;
	}
}

static void	clear_redirs(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		free(redir);
		redir = next;
	}
}
