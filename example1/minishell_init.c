/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:17:21 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/24 18:03:49 by fporciel         ###   ########.fr       */
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

void	msh_clean_pipeline(t_input *init)
{
	int		i;
	t_cmd	*tmp;

	if (init->cmds)
	{
		while (init->cmds)
		{
			if (init->cmds->name)
				free(init->cmds->name);
			if (init->cmds->argv)
				i = msh_matdel2(&init->cmds->argv);
			tmp = init->cmds;
			init->cmds = init->cmds->next;
			free(tmp);
			(void)i;
		}
	}
}

void	msh_init(t_input *init)
{
	init->cmds = NULL;
	init->toks = NULL;
	init->line = NULL;
	init->i = 0;
	init->redirflag = 0;
	init->exit_status = 0;
	init->errtok = 0;
	init->space = 0;
	init->errquote = 1;
	init->heredoc = 0;
}

void	msh_memset(t_input *init)
{
	t_tok	*tmp;
	t_tok	*tmp2;

	if (init->line)
		free(init->line);
	msh_clean_pipeline(init);
	if (init->toks)
	{
		tmp = init->toks;
		while (tmp)
		{
			if (tmp->str)
				free(tmp->str);
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2);
		}
	}
	msh_init(init);
}

void	msh_clean_init(t_input **init)
{
	msh_memset(*init);
	(void)msh_matdel(&(*init)->envp);
	free(*init);
}
