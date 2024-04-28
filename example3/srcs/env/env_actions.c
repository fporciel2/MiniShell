/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:36:24 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/04/17 22:36:37 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_set_get_value(t_env *env, char *value, int append)
{
	if (env->value)
	{
		if (append)
			value = ft_strjoin(env->value, value);
		else
			value = ft_strdup(value);
		if (!value)
			return (NULL);
		free(env->value);
	}
	else
		value = ft_strdup(value);
	return (value);
}

int	env_set(t_env **env_head, char *name, char *value, int append)
{
	t_env	*env;

	env = env_get_elm(*env_head, name);
	if (env && value)
	{
		value = env_set_get_value(env, value, append);
		env->value = value;
		if (!env->value)
			return (1);
	}
	else if (!env)
	{
		env = env_init_elm(name, value);
		if (!env)
			return (1);
		env_append(env_head, env);
	}
	return (0);
}

void	env_unset(t_env **env_head, char *name)
{
	t_env	*env;
	t_env	*prev;

	env = *env_head;
	prev = NULL;
	while (env)
	{
		if (str_equals(env->name, name))
		{
			if (prev)
				prev->next = env->next;
			else
				*env_head = env->next;
			free(env->name);
			free(env->value);
			free(env);
			env = NULL;
			return ;
		}
		prev = env;
		env = env->next;
	}
}

t_env	*env_get_elm(t_env *env_head, char *name)
{
	while (env_head)
	{
		if (str_equals(env_head->name, name))
			return (env_head);
		env_head = env_head->next;
	}
	return (NULL);
}

char	*env_get(t_env *env_head, char *name)
{
	t_env	*env;

	env = env_get_elm(env_head, name);
	if (env)
		return (env->value);
	return (NULL);
}
