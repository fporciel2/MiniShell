/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_cleaner.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:30:29 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/25 15:16:53 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ´MiniShell´ is a simple shell for Debian GNU/Linux.
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

void	msh_split_clean_command(char **command)
{
	ssize_t	j;

	if (!command)
		return ;
	j = 0;
	while (command[j])
		j++;
	j--;
	while (j >= 0)
	{
		free(command[j]);
		j--;
	}
	free(command);
	command = NULL;
}

void	msh_split_clean_pipeline(t_input *init)
{
	ssize_t	j;

	if (!init->pipeline)
		return ;
	j = 0;
	while (init->pipeline[j])
		j++;
	j--;
	while (j >= 0)
	{
		msh_split_clean_command(init->pipeline[init->pipe_count]);
		j--;
	}
	free(init->pipeline);
	init->pipeline = NULL;
}
