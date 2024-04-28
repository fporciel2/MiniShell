/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:36:46 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/04/17 22:38:09 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_from_str(char *env_str)
{
	int		split_i;
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	split_i = env_find_split_index(env_str);
	if (split_i == -1)
		env->name = ft_strdup(env_str);
	else
		env->name = ft_substr(env_str, 0, split_i);
	if (!env->name)
		return (free(env), NULL);
	if (split_i != -1)
	{
		env->value = ft_substr(env_str, split_i + 1,
				ft_strlen(env_str) - split_i);
		if (!env->value)
			return (free(env->name), free(env), NULL);
	}
	else
		env->value = NULL;
	env->next = NULL;
	return (env);
}

t_env	*env_init(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*env;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		if (!env)
		{
			env = env_from_str(envp[i]);
			head = env;
		}
		else
		{
			env->next = env_from_str(envp[i]);
			env = env->next;
		}
		if (!env)
			return (free_env(&head), NULL);
		i++;
	}
	return (head);
}

t_env	*env_init_elm(char *name, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = ft_strdup(name);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
	if (!env->name || (value && !env->value))
		return (free(env), NULL);
	env->next = NULL;
	return (env);
}
