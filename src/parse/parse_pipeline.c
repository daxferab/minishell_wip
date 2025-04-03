#include "minishell.h"

void	parse_pipeline(t_smash *smash)
{
	int		cmd_num;
	t_token	*current;
	t_token	*before;
	
	current = smash->first_token;
	while (current->next)
	{
		cmd_num = 0;
		before = NULL;
		while (current->next && current->next->type != PIPE)
		{
			if (is_word(current->type) && (!before || !is_redirection(before->type)))
				cmd_num++;
			before = current;
			current = current->next;
		}
	}
}
