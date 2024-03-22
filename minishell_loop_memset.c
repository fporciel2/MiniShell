/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop_memset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:33:50 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/22 16:11:48 by fporciel         ###   ########.fr       */
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

static char	**msh_remove_matrix(char **matrix)
{
	ssize_t	j;

	if (!matrix)
		return (NULL);
	j = 0;
	while (matrix[j])
		j++;
	j--;
	while (j >= 0)
	{
		free(matrix[j]);
		j--;
	}
	return (NULL);
}

static char	***msh_remove_pipeline(char ***pipeline)
{
	ssize_t	j;

	if (!pipeline)
		return (NULL);
	j = 0;
	while (pipeline[j])
		j++;
	j--;
	while (j >= 0)
	{
		pipeline[j] = msh_remove_matrix(pipeline[j]);
		j--;
	}
	return (NULL);
}

void	msh_loop_memset(t_input *init)
{
	init->envp = msh_remove_matrix(init->envp);
	if (init->string)
		free(init->string);
	init->string = NULL;
	init->pipeline = msh_remove_pipeline(init->pipeline);
	init->pipe_count = 0;
	init->token_count = 0;
	init->i = 0;
	init->open_quote = START;
	init->quote_state = NORMAL;
	init->pipe_state = START;
}

void	msh_loop_clean_all(t_input *init)
{
	msh_loop_memset(init);
	free(init);
}
