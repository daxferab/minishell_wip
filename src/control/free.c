#include "minishell.h"

void	free_t_envp(t_envp *envp)
{
	t_envp	*tmp;

	while (envp)
	{
		free(envp->key);
		free(envp->value);
		tmp = envp;
		envp = envp->next;
		free(tmp);
	}
	free(envp);
}

void	free_smash(t_smash smash)
{
	free_t_envp(smash.envp);
	free(smash.cwd);
	free(smash.history_file);
	smash.envp = NULL;
	smash.cwd = NULL;
	smash.history_file = NULL;
	rl_clear_history();
}

bool	free_node(t_envp *envp, char *key)
{
	t_envp	*prev;

	prev = envp;
	while (envp)
	{
		if (ft_str_equals(envp->key, key))
		{
			prev->next = envp->next;
			free(envp->key);
			free(envp->value);
			free(envp);
			return (true);
		}
		prev = envp;
		envp = envp->next;
	}
	return (false);
}
