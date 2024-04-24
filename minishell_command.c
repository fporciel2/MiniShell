/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:41:16 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/24 10:15:04 by fporciel         ###   ########.fr       */
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

int	msh_new_command(t_input *init, t_tok *tok)
{
	t_cmd	*new;
	t_cmd	*tmp;

	tmp = init->cmds;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return (perror("Error"), 1);
	new->name = msh_strdup(tok->str);
	if (!new->name)
		return (perror("Error"), 1);
	new->argv = NULL;
	new->envp = init->envp;
	new->next = NULL;
	if (!tmp)
		init->cmds = new;
	else
		tmp->next = new;
	new->prev = tmp;
	return (0);
}

int	msh_new_arg(t_input *init, t_tok *tok)
{
	t_cmd	*tmp;

	tmp = init->cmds;
	if (!tmp)
		return (msh_new_command(init, tok));
	while (tmp->next)
		tmp = tmp->next;
	if (!tmp->name)
	{
		if (msh_new_command(init, tok))
			return (1);
	}
	return (msh_arg_setting(init, tok, tmp));
}
