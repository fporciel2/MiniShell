/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 06:36:39 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/24 07:10:14 by fporciel         ###   ########.fr       */
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

static void	msh_copy_strtok(t_input *init, t_tok *tmp, char **str)
{
	if (tmp->str)
	{
		while (tmp->str[init->j])
		{
			(*str)[init->j] = tmp->str[init->j];
			init->j++;
		}
	}
	(*str)[init->j] = init->line[init->i];
	(*str)[init->j + 1] = 0;
}


int	msh_new_char(t_input *init)
{
	t_tok	*tmp;
	char	*str;

	if (!init->toks)
		return (msh_new_token(init));
	tmp = init->toks;
	init->j = 0;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->str)
		str = (char *)malloc(sizeof(char) * (msh_strlen(tmp->str) + 2));
	else
		str = (char *)malloc(sizeof(char) * 2);
	if (!str)
		return (perror("Error"), 1);
	msh_copy_strtok(init, tmp, &str);
	free(tmp->str);
	tmp->str = str;
	return (0);
}

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

static int	msh_next_token(t_input *init)
{
	t_tok	*tmp;
	t_tok	*new;

	tmp = init->toks;
	new = (t_tok *)malloc(sizeof(t_tok));
	if (!new)
		return (perror("Error"), 1);
	if (init->line[init->i] == 124)
		new->type = 1;
	else if ((init->line[init->i] == 60) || (init->line[init->i] == 62))
		new->type = 2;
	else if ((init->line[init->i] == 34) || (init->line[init->i] == 39))
		new->type = 3;
	else
		new->type = 0;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
	new->index = tmp->index + 1;
	return (msh_new_char(init));
}

int	msh_new_token(t_input *init)
{
	if (!init->toks)
		return (msh_first_token(init));
	else
		return (msh_next_token(init));
}
