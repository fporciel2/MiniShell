/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_handle_sigint_close_on_error.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:12:50 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/25 16:18:41 by fporciel         ###   ########.fr       */
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

static void	msh_destroy_matrix(char **matrix)
{
	ssize_t	j;

	if (!matrix)
		return ;
	j = 0;
	while (matrix[j])
		j++;
	j--;
	while (j >= 0)
	{
		free(matrix[j]);
		j--;
	}
	free(matrix);
}

void	msh_handle_sigint_close_on_error(const t_input *init)
{
	ssize_t	j;

	j = 0;
	if (init->string)
		free(init->string);
	msh_destroy_matrix(init->envp);
	if (init->pipeline)
	{
		while (init->pipeline[j])
		{
			msh_destroy_matrix(init->pipeline[j]);
			j++;
		}
	}
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}
