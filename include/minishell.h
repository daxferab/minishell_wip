#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/******************************************************************************/
/*                                   MACROS                                   */
/******************************************************************************/

/******************************************************************************/
/*                                   ENUMS                                    */
/******************************************************************************/

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

/******************************************************************************/
/*                                  STRUCTS                                   */
/******************************************************************************/

typedef struct s_redir
{
	t_token_type	type;
	char			*value;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipeline
{
	char				**cmd;
	t_redir				*redir_lst;
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
	t_token		*first_token;
	t_token		*last_token;
	t_pipeline	*first_pipeline;
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

// history.c

void	import_history(t_smash *smash);
void	add_history_entry(t_smash *smash);

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

/******************************************************************************/
/*                            FUNCTIONS - EXECUTION                           */
/******************************************************************************/

void	input_handler(t_smash *smash, char **input);

/******************************************************************************/
/*                             FUNCTIONS - PARSE                              */
/******************************************************************************/

bool	add_token(t_smash *smash, int start, int len, t_token_type type);
void	clear_input(t_smash *smash);
bool	get_variable(t_smash *smash, int pos);
void	parse_pipeline(t_smash *smash);
void	read_line(t_smash *smash);
bool	syntax(t_smash *smash);
bool	is_redirection(t_token_type type);
bool	is_word(t_token_type type);
bool	tokenize(t_smash *smash);

#endif