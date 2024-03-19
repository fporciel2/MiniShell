/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:51:53 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/19 12:22:26 by fporciel         ###   ########.fr       */
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

static void	msh_init_pipeline(t_input *init)
{
	init->pipeline = (char ***)malloc(sizeof(char **) * 2);
	if (!init->pipeline)
		msh_close_on_error(init);
	init->pipeline[1] = NULL;
	init->pipeline[0] = (char **)malloc(sizeof(char *) * 2);
	if (!init->pipeline[0])
		msh_close_on_error(init);
	init->pipeline[0][1] = NULL;
	init->pipeline[0][0] = (char *)malloc(sizeof(char) * 2);
	if (!init->pipeline[0][0])
		msh_close_on_error(init);
	init->pipeline[0][0][1] = 0;
}

void	msh_split_token(t_input *init)
{
	if (init->i == 0)
		msh_init_pipeline(init);
}

void	msh_split_pipeline(t_input *init)
{
	if (init->i == 0)
		msh_init_pipeline(init);
}

void	msh_append_char(t_input *init)
{
	if (init->i == 0)
		msh_init_pipeline(init);
}
