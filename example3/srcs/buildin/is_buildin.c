/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_buildin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:36:20 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/04/24 13:05:09 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Check if name of cmd is a buildin command
if it is, return a pointer to the function
else return NULL
*/
t_bdn_func	ft_is_buildin(t_cmd *cmd)
{
	t_bdn_func	result;

	if (cmd->buildin)
		return (cmd->buildin);
	result = NULL;
	if (!ft_strncmp(cmd->name, "echo", 5))
		result = ft_echo;
	else if (!ft_strncmp(cmd->name, "pwd", 4))
		result = ft_pwd;
	else if (!ft_strncmp(cmd->name, "export", 7))
		result = ft_export;
	else if (!ft_strncmp(cmd->name, "cd", 3))
		result = ft_cd;
	else if (!ft_strncmp(cmd->name, "unset", 6))
		result = ft_unset;
	else if (!ft_strncmp(cmd->name, "env", 4))
		result = ft_env;
	else if (!ft_strncmp(cmd->name, "exit", 5))
		result = ft_exit;
	cmd->buildin = result;
	return (result);
}
