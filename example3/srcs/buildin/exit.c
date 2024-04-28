/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:32:20 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/04/24 15:32:58 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* exit -> old_exit
* exit non-numeric .* -> 2
* exit numeric -> atoi % 256 (exit code must be 0-255)
* exit numeric .* -> too many arguments -> -1
* if return -1 do not exit and replace with 1
*/
static int	exit_exit_code(t_cmd *cmd, int old_exit)
{
	if (cmd->argc <= 1)
		return (old_exit);
	if (!ft_isstrdigit(cmd->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	if (cmd->argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (-1);
	}
	return (ft_atoi(cmd->argv[1]) % 256);
}

/*
*	Check only syntax and print error
*	Return the exit code
*/
int		ft_exit(t_cmd *cmd, t_mshell *mini)
{
	int	code;

	code = exit_exit_code(cmd, mini->exit_code);
	if (code == -1)
		code = 1;
	return (code);
}

/*
*	Check if cmd is exit
*	Check for pipes
*/
static int	to_exit(t_cmd *cmd)
{
	return ((ft_is_buildin(cmd) == ft_exit) &&
		!cmd->next && !cmd->prev);
}

/*
*	Check if the cmd is exit
*	Check the syntax
*	If no pipes, return 1 (exit) and print exit
*/
int	check_exit(t_mshell *mshell)
{
	int code;

	if (!to_exit(mshell->cmd))
		return (0);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	code = exit_exit_code(mshell->cmd, mshell->exit_code);
	if (code != -1)
	{
		mshell->to_exit = 1;
		mshell->exit_code = code;
	}
	else
		mshell->exit_code = 1;
	return (1);
}
