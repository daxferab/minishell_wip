#include "minishell.h"

static t_smash	init(int argc, char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_smash	smash;

	smash = init(argc, argv, envp);
	while (true)
	{
		parse_line(&smash);
		if (!smash.user_input)
			break ;
		execute(&smash);
		clear_input(&smash);
	}
	free_smash(smash);
	return (0);
}

static t_smash	init(int argc, char **argv, char **envp)
{
	t_smash	smash;

	ft_printf("Minishell\n");
	smash.debug_mode = argc > 1 && ft_str_equals(argv[1], "debug");
	smash.envp = init_envp(envp);
	//TODO: Handle error
	smash.cwd = getcwd(NULL, 0);
	smash.first_token = NULL;
	smash.last_token = NULL;
	smash.exit_status = 0;
	smash.history_file = NULL;
	import_history(&smash);
	return (smash);
}
