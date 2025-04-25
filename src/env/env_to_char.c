#include "minishell.h"

static int	lstlen(t_envp *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 1;
	while (lst->next)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

static	char	*create_line(char *s1, char *s2, char *s3)
{
	char	*line;

	line = ft_strjoin(s1, s2);
	if (!line)
		return (ft_putstr_fd("Malloc error", 2), NULL);
	line = ft_strjoin(line, s3);
	if (!line)
		return (ft_putstr_fd("Malloc error", 2), NULL);
	return (line);
}

char	**env_to_char(t_envp *env_lst)
{
	char	**envp;
	char	*line;
	int		i;

	i = 0;
	envp = malloc((lstlen(env_lst) + 1) * sizeof(t_envp));
	if (!envp)
		return (ft_putstr_fd("Malloc error", 2), NULL);
	while (env_lst)
	{
		line = create_line(env_lst->key, "=", env_lst->value);
		if (!line)
			return (ft_free_double_pointer((void **)envp), NULL);
		envp[i] = ft_strdup(line);
		if (!envp[i])
			return (ft_putstr_fd("Malloc error", 2), free(line),\
			ft_free_double_pointer((void **)envp), NULL);
		free(line);
		env_lst = env_lst->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
