#include "minishell.h"

//TODO refactor to admit at least \001 and \002, maybe all?
//TODO calculate chars beforehand and allocate just for those
//TODO free
char	*parse_octals(char *prompt)
{
	char	*new;
	int		prompt_iter;
	int		new_iter;

	new = ft_strdup(prompt);
	prompt_iter = 0;
	new_iter = 0;
	while (prompt[prompt_iter])
	{
		if (prompt[prompt_iter] == '\\' && prompt[prompt_iter + 1] == '0' && prompt[prompt_iter + 2] == '3' && prompt[prompt_iter + 3] == '3')
		{
			new[new_iter] = '\033';
			new_iter++;
			prompt_iter += 4;
		}
		else
		{
			new[new_iter] = prompt[prompt_iter];
			new_iter++;
			prompt_iter++;
		}
	}
	new[new_iter] = '\0';
	return (new);
}

char	*prompt(t_smash *smash, bool in_heredoc)
{
	char	*prompt;

	if (in_heredoc)
	{
		prompt = get_value(smash->envp, "PS2");
		if (!prompt)
			prompt = HEREDOC_PROMPT;
	}
	else
	{
		prompt = get_value(smash->envp, "PS1");
		if (!prompt)
			prompt = PROMPT;
	}
	//prompt = parse_octals(prompt);
	if (smash->debug_mode)
	{
		ft_printf(prompt);
		return (ft_get_next_line_no_nl(STDIN_FILENO));
	}
	return (readline(prompt));
}
