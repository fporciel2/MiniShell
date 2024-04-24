/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:30:37 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/24 17:46:31 by fporciel         ###   ########.fr       */
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

int	msh_check_pipe(t_tok *tok)
{
	if (!tok->prev || !tok->next || (tok->prev->type == 1)
		|| (tok->next->type == 1))
		return (msh_print("Syntax error: wrong pipe\n"), 1);
	return (0);
}

int	msh_check_redir(t_tok *tok)
{
	if ((!tok->prev && !tok->next) || (tok->prev && (tok->prev->type == 2))
		|| (tok->next && ((tok->next->type == 2) || (tok->next->type == 1))))
		return (msh_print("Syntax error: wrong redirection\n"), 1);
	return (0);
}

int	msh_parser(t_input *init)
{
	t_tok	*tmp;

	tmp = init->toks;
	if (!tmp || !tmp->str || (tmp->str[0] == 124))
		return (msh_print("Syntax error: wrong token\n"), 0);
	while (tmp && !init->errtok)
	{
		if (!tmp)
			break ;
		if (tmp->type == 1)
			init->errtok = msh_check_pipe(tmp);
		else if (tmp->type == 2)
			init->errtok = msh_new_redir(init, tmp);
		else if ((tmp->prev && (tmp->prev->type == 1)) || (tmp == init->toks))
			init->errtok = msh_new_cmd(init, tmp);
		else
			init->errtok = msh_new_arg(init, tmp);
		tmp = tmp->next;
	}
	if (init->cmds)
	{
		t_cmd	*tmp1 = init->cmds;
		while (tmp1)
		{
			printf("CMD: %s %d\n\n", tmp1->name, tmp1->redir);
			ssize_t	i = 0;
			while (tmp1->argv && tmp1->argv[i])
				printf("ARG: %s\n", tmp1->argv[i++]);
			printf("\n\n");
			tmp1 = tmp1->next;
		}
	}
	if (init->errtok)
		return (msh_print("\n0 EXIT\n"), 0);
	return (msh_print("\n1 EXIT\n"), 1);
}
