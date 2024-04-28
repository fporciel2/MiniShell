/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:30:23 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/04/24 15:15:18 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_path(t_env **env_head)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) == NULL)
		return (1);
	env_set(env_head, "OLDPWD", env_get(*env_head, "PWD"), 0);
	env_set(env_head, "PWD", buf, 0);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_mshell *mini)
{
	char	*path;

	if (cmd->argc == 1)
	{
		path = env_get(mini->env, "HOME");
		if (!path)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	}
	else if (cmd->argc != 2)
		return (ft_putstr_fd("cd: wrong number of arguments\n", 2), 1);
	else if (str_equals(cmd->argv[1], "-"))
		path = env_get(mini->env, "OLDPWD");
	else
		path = cmd->argv[1];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		return (1);
	}
	return (update_path(&mini->env));
}
