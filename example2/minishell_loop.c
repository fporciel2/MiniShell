/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:25:24 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/18 12:28:06 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* `MiniShell` is a simple shell for Debian GNU/Linux.
 * Copyright (C) 2024 Federico Porciello
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * For more information on how to contact me by electronic and paper mail
 * please see:
 * https://github.com/fporciel2/MiniShell
 */

#include "minishell.h"

static t_cmd	*msh_clean_constr(t_cmd *cmds)
{
	t_cmd	*tmp;
	t_cmd	*tmp1;

	tmp = cmds;
	if (tmp == NULL)
		return (NULL);
	while (tmp)
	{
		tmp1 = tmp;
		free(tmp->name);
		tmp->argv = msh_clean_matrix(tmp->argv);
		tmp = tmp->next;
		free(tmp1);
	}
	return (tmp);
}

static void	msh_memset(t_input *init)
{
	init->cmds = msh_clean_constr(init->cmds);
	init->pipeline = msh_clean_pipeline(init->pipeline);
	init->line = msh_clean_str(init->line);
	init->cmds = msh_clean_cmds(init->cmds);
}

static void	msh_free_init(t_input *init)
{
	init->cmds = msh_clean_constr(init->cmds);
	init->envp = msh_clean_cmd(init->envp);
	init->pipeline = msh_clean_pipeline(init->pipeline);
	init->line = msh_clean_str(init->line);
	init->prompt = NULL;
	free(init);
}

int	msh_loop(t_input *init)
{
	int	exit_minishell;

	exit_minishell = 0;
	while (42)
	{
		msh_memset(init);
		init->line = readline("MiniShell> ");
		if (!init->line)
		{
			exit_minishell = init->exit_minishell;
			init->i = write(1, "exit\n", 5);
			msh_free_init(init);
			break ;
		}
		else if (*init->line)
			add_history(init->line);
		else
			continue ;
		if (!msh_strtok(init) || !msh_tokcmd(init)
			|| !msh_parsing(init->cmds, init))
			continue ;
	}
	return (exit_minishell);
}
