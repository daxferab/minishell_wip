#include "minishell.h"


int	cmd_echo(char **input)
{
	int		i;
	bool	nl;

	i = 1;
	nl = true;
	while (input[i] && ft_str_equals(input[i], "-n"))
	{
		nl = false;
		i++;
	}
	while (input[i])
	{
		ft_printf("%s", input[i]);
		i++;
		if (input[i])
			ft_printf(" ");
	}
	if (nl)
		ft_printf("\n");
	return (0);
}
