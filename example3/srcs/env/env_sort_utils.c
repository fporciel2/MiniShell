#include "minishell.h"

static void	env_cpy_helper(t_env **cpy, t_env *env, t_env **tmp)
{
	if (!*tmp)
	{
		*tmp = env_init_elm(env->name, env->value);
		if (!*tmp)
			return ;
		*cpy = *tmp;
	}
	else
	{
		(*tmp)->next = env_init_elm(env->name, env->value);
		if (!(*tmp)->next)
			return ;
		*tmp = (*tmp)->next;
	}
}

t_env	*env_cpy(t_env *env_head)
{
	t_env	*cpy;
	t_env	*tmp;
	t_env	*env;

	tmp = NULL;
	cpy = NULL;
	env = env_head;
	while (env)
	{
		env_cpy_helper(&cpy, env, &tmp);
		if (!cpy)
			return (NULL);
		env = env->next;
	}
	return (cpy);
}
