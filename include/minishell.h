#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	LITERAL,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	INPUT,
	HEREDOC,
	OUTPUT,
	APPEND,
	PIPE
}	t_token_type;

typedef struct s_var
{
	bool			valid_name;
	int				pos;
	char			*value;
	int				key_len;
	int				value_len;
	struct s_var	*next;
}	t_var;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_var			*first_variable;
	t_var			*last_variable;
	struct s_token	*next;
}	t_token;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_smash
{
	char	*user_input;
	bool	debug_mode;
	t_envp	*envp;
	char	*cwd;
	int		exit_status;
	t_token	*first_token;
	t_token	*last_token;
}	t_smash;

// DEBUG

void	debug_int(t_smash *smash, char *variable, int value);
void	debug_string(t_smash *smash, char *variable, char *value);
void	debug_tokens(t_smash *smash);

//READ_LINE

void	clear_input(t_smash *smash);
void	read_line(t_smash *smash);

//BUILTINS

bool	cmd_cd(t_smash *smash, char **input);
bool	cmd_echo(char **input);
bool	cmd_env(t_smash smash, char **input);
bool	cmd_pwd(t_smash *smash, char **input);
bool	cmd_unset(t_smash *smash, char **input);
bool	cmd_export(t_smash *smash, char **input);

// envlist.c
char	*get_value(t_envp *envp, char *key);
bool	new_entry(t_envp **envp, char *key, char *value);
bool	update_envp(t_envp **envp, char	*key, char *newvalue);
void	display_envp(t_envp *envp);
t_envp	*init_envp(char **envp);

//envutils.c
char	**split_char(char *envp, char c);
t_envp	*new_node(char *key, char *value);
void	addnode_front(t_envp *node, t_envp **envp);
int		envsize(t_envp *lst);
bool	is_valid_key(char *key);

// free.c
void	free_smash(t_smash smash);
void	free_t_envp(t_envp *envp);
bool	free_node(t_envp *envp, char *key);

// inputhandler.c
void	input_handler(t_smash *smash, char **input);

// var_handler.c
bool	valid_char(char c);
void	get_var(t_smash *smash, int pos);

#endif