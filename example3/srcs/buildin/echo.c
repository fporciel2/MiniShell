/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:30:32 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/04/24 15:15:29 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd, t_mshell *mini)
{
	int		add_newline;
	char	**argv;

	(void)mini;
	add_newline = 1;
	if ((cmd->argc == 1) || (!cmd->argv))
	{
		printf("\n");
		return (0);
	}
	argv = cmd->argv + 1;
	if (*argv && (ft_strncmp(*argv, "-n", 3) == 0))
	{
		add_newline = 0;
		argv++;
	}
	while (*argv)
	{
		printf("%s", *argv++);
		if (*argv)
			printf(" ");
	}
	if (add_newline)
		printf("\n");
	return (0);
}
