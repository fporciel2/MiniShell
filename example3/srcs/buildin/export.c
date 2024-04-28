/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:32:32 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/04/24 15:16:24 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_print(t_env *env_head)
{
	t_env	*sorted_env;
	t_env	*env;

	sorted_env = env_sort(env_head);
	if (!sorted_env)
		return (1);
	env = sorted_env;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf("declare -x %s\n", env->name);
		env = env->next;
	}
	free_env(&sorted_env);
	return (0);
}

static int	export_error(char *str)
{
	perror("minishell: export: \'");
	perror(str);
	perror("\': not a valid identifier");
	return (1);
}

static int	export_check_error(char *env_str)
{
	int	i;

	i = -1;
	if (!*env_str)
		return (export_error(env_str));
	if (*env_str == '=')
		return (export_error(env_str));
	if (ft_isdigit(*env_str))
		return (export_error(env_str));
	while (env_str[i] && (env_str[i] != '='))
	{
		if (!ft_isalnum(env_str[i++]))
			return (export_error(env_str));
	}
	return (0);
}

// static int	

static int	export_set(t_env **env_head, char *env_str)
{
	int		split_i;
	int		name_len;
	int		append;
	char	*name;
	char	*val;

	if (export_check_error(env_str))
		return (1);
	split_i = env_find_split_index(env_str);
	append = 0;
	if (split_i == -1)
		return (env_set(env_head, env_str, NULL, 0));
	name_len = split_i;
	if ((env_str[name_len - 1] == '+'))
		append = 1;
	name = ft_substr(env_str, 0, name_len - append);
	if (!name)
		return (1);
	val = ft_substr(env_str, split_i + 1, ft_strlen(env_str) - split_i);
	if (!val)
		return (free(name), 1);
	if (env_set(env_head, name, val, append))
		return (free(name), free(val), 1);
	return (free(name), free(val), 0);
}

int	ft_export(t_cmd *cmd, t_mshell *mini)
{
	char	**argv;

	if (cmd->argc == 1)
		return (export_print(mini->env));
	argv = cmd->argv + 1;
	while (*argv)
	{
		if (export_set(&mini->env, *argv))
			return (1);
		argv++;
	}
	return (0);
}
