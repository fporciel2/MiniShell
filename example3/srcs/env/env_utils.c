#include "minishell.h"

int	env_find_split_index(char *env_str)
{
	int	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	if (!env_str[i])
		return (-1);
	return (i);
}

// poi diventerà un comando (andrà però gestito fdout)
void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

void	env_append(t_env **env_head, t_env *new_env)
{
	t_env	*env;

	if (!*env_head)
	{
		*env_head = new_env;
		return ;
	}
	env = *env_head;
	while (env->next)
		env = env->next;
	env->next = new_env;
}

static char	*join_env_line(char *name, char *value)
{
	char	*tmp;
	char	*env_line;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	env_line = ft_strjoin(tmp, value);
	free(tmp);
	return (env_line);
}

char	**env_to_array(t_env *env_head)
{
	t_env	*env;
	char	**env_array;
	int		i;

	env = env_head;
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	env_array = (char **) malloc(sizeof(char *) * (i + 1));
	if (!env_array)
		return (NULL);
	env_array[i] = NULL;
	env = env_head;
	i = 0;
	while (env)
	{
		env_array[i] = join_env_line(env->name, env->value);
		if (!env_array[i++])
			return (free_env_array(env_array), NULL);
		env = env->next;
	}
	return (env_array);
}
