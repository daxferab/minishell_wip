#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

/******************************************************************************/
/*                                   MACROS                                   */
/******************************************************************************/

# define PIPE_READ	STDIN_FILENO
# define PIPE_WRITE	STDOUT_FILENO

/******************************************************************************/
/*                                   ENUMS                                    */
/******************************************************************************/

typedef enum e_token_type
{
	LITERAL			= 0,
	SINGLE_QUOTE	= 1,
	DOUBLE_QUOTE	= 2,
	INPUT			= 3,
	HEREDOC			= 4,
	OUTPUT			= 5,
	APPEND			= 6,
	PIPE			= 7
}	t_token_type;

typedef enum e_exit_code
{
	EC_SUCCESS					= 0,
	EC_ERROR					= 1,
	EC_FILE_NOT_FOUND			= 2,
	EC_COMMAND_NOT_EXECUTABLE	= 126,
	EC_COMMAND_NOT_FOUND		= 127
}	t_exit_code;

/******************************************************************************/
/*                                  STRUCTS                                   */
/******************************************************************************/

typedef struct s_redir
{
	t_token_type	type;
	char			*value;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipeline
{
	char				**cmd;
	t_redir				*redir_lst;
	int					fd_in;
	int					fd_out;
	struct s_pipeline	*next;
}	t_pipeline;

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
	char		*user_input;
	bool		debug_mode;
	t_envp		*envp;
	char		*cwd;
	int			exit_status;
	char		*history_file;
	t_token		*first_token;
	t_token		*last_token;
	t_pipeline	*first_pipeline;
	int			fd_stdin;
	int			fd_stdout;
}	t_smash;

/******************************************************************************/
/*                                 FUNCTIONS                                  */
/******************************************************************************/

/******************************************************************************/
/*                            FUNCTIONS - BUILTINS                            */
/******************************************************************************/

int		cmd_cd(t_smash *smash, char **input);
int		cmd_echo(char **input);
int		cmd_env(t_smash smash, char **input);
int		cmd_exit(t_smash *smash, char **input);
int		cmd_export(t_smash *smash, char **input);
int		cmd_pwd(t_smash *smash, char **input);
int		cmd_unset(t_smash *smash, char **input);

/******************************************************************************/
/*                            FUNCTIONS - CONTROL                             */
/******************************************************************************/

//debug.c

void	debug_int(t_smash *smash, char *variable, int value);
void	debug_string(t_smash *smash, char *variable, char *value);
void	debug_tokens(t_smash *smash);

// free.c

void	free_smash(t_smash smash);
void	free_t_envp(t_envp *envp);
bool	free_node(t_envp *envp, char *key);
void	free_redir(t_redir *redir);
void	free_pipeline(t_pipeline *pipeline);

// history.c

void	import_history(t_smash *smash);
void	add_history_entry(t_smash *smash);

void	sig_init();

/******************************************************************************/
/*                              FUNCTIONS - ENV                               */
/******************************************************************************/

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

//env_to_char.c

char	**env_to_char(t_envp *env_lst);

/******************************************************************************/
/*                            FUNCTIONS - EXECUTION                           */
/******************************************************************************/

bool	execute_builtins(t_smash *smash, t_pipeline *pipeline);
void	execute_command(t_smash *smash, t_pipeline *pipeline, pid_t *pid);
void	execute_external(t_smash *smash, t_pipeline *pipeline);
void	execute(t_smash *smash);
t_exit_code	get_command(char **path, char *command, char **path_command);
void	handle_redirections(t_smash *smash);

/******************************************************************************/
/*                             FUNCTIONS - PARSE                              */
/******************************************************************************/

bool	get_variable(t_smash *smash, t_token *token, int pos);
bool	parse_pipeline(t_smash *smash);
bool	parse_line(t_smash *smash);
bool	remove_quotes(t_smash *smash);
bool	syntax(t_smash *smash);
bool	tokenize(t_smash *smash);

// clear_input.c

void	clear_input(t_smash *smash);
void	clear_tokens(t_token *token);

// expand_variables.c

bool	expand_variables(t_smash *smash);
bool	expand_token(t_smash *smash, t_token *token);

// token_type.c

void	get_token_type(t_token_type *type, char *c);
void	mutate(t_token_type *type, char c);
bool	is_redirection(t_token_type type);
bool	is_word(t_token_type type);

#endif
