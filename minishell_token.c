/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 06:36:39 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/24 06:46:07 by fporciel         ###   ########.fr       */
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

static int	msh_first_token(t_input *init)
{
	init->toks = (t_tok *)malloc(sizeof(t_tok));
	if (!init->toks)
		return (perror("Error"), 1);
	if (init->line[init->i] == 124)
		init->toks->type = 1;
	else if ((init->line[init->i] == 60) || (init->line[init->i] == 62))
		init->toks->type = 2;
	else if ((init->line[init->i] == 34) || (init->line[init->i] == 39))
		init->toks->type = 3;
	else
		init->toks->type = 0;
	init->toks->index = 0;
	init->toks->next = NULL;
	init->toks->prev = NULL;
	return (msh_new_char(init));
}

int	msh_new_token(t_input *init)
{
	if (!init->toks)
		return (msh_first_token(init));
	else
		return (msh_next_token(init));
}
