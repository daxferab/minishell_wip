#include "minishell.h"

static t_smash	init(int argc, char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_smash	smash;

	smash = init(argc, argv, envp);
	if (smash.exit_status == 1)
		return (free_smash(smash), ft_putstr_fd("Error initializing smash\n", 2), 1);
	while (true)
	{
		sig_init();
		if (!parse_line(&smash) || (smash.user_input && !smash.user_input[0]))
		{
			clear_input(&smash);
			continue ;
		}
		if (!smash.user_input)
			break ;
		if (!execute(&smash))
			break ;
	}
	free_smash(smash);
	return (0);
}

static t_smash	init(int argc, char **argv, char **envp)
{
	t_smash	smash;

	smash.debug_mode = argc > 1 && ft_str_equals(argv[1], "debug");
	smash.exit_status = 0;
	smash.envp = init_envp(envp);
	smash.cwd = getcwd(NULL, 0);
	if (!smash.envp || !smash.cwd)
		smash.exit_status = 1;
	smash.first_token = NULL;
	smash.last_token = NULL;
	smash.first_pipeline = NULL;
	smash.history_file = NULL;
	import_history(&smash);
	return (smash);
}
//TODO: protect builtins mallocs