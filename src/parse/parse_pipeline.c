#include "minishell.h"

static int	get_cmd_num(t_token *current)
{
	int		cmd_num;

	t_token	*before;
	cmd_num = 0;
	before = NULL;
	while (current->next || current->type == PIPE)
	{
		if (is_word(current->type) && (!before || !is_redirection(before->type)))
		{
			ft_printf_fd(STDERR_FILENO, "Word: %s\n", current->value);
			cmd_num++;
		}
		before = current;
		current = current->next;
	}
	return (cmd_num);
}

void	parse_pipeline(t_smash *smash)
{
	int		cmd_num;
	t_token	*current;
	
	current = smash->first_token;
	cmd_num = get_cmd_num(current);
	debug_int(smash, "cmd_num", cmd_num);
	(void)cmd_num;
}
