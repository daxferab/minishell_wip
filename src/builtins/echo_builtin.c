#include "minishell.h"

bool	cmd_echo(char **input)
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
	if (input[i] && !ft_strncmp(input[1], "-", 1))
		return (false);
	while (input[i])
	{
		printf("%s", input[i]);
		i++;
		if (input[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (true);
}
