/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:51:53 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/20 15:59:13 by fporciel         ###   ########.fr       */
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

static void	msh_clean_current_matrix(t_input *init)
{
	size_t	
}

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
	init->pipeline[0][0][0] = init->string[init->i];
	init->pipe_count = 0;
	init->token_count = 0;
}

void	msh_split_pipeline(t_input *init)
{
	if (init->i == 0)
	{
		msh_init_pipeline(init);
		return ;
	}
}

void	msh_split_token(t_input *init)
{
	char	**matrix;
	size_t	j;

	if (init->i == 0)
	{
		msh_init_pipeline(init);
		return ;
	}
	j = 0;
	init->token_count++;
	matrix = (char **)malloc(sizeof(char *) * (init->token_count + 2));
	if (!matrix)
		msh_close_on_error(init);
	while (init->pipeline[init->pipe_count][j])
	{
		matrix[j] = init->pipeline[init->pipe_count][j];
		j++;
	}
	matrix[j] = NULL;
	msh_clean_current_matrix(init);
	init->pipeline[init->pipe_count] = matrix;
	msh_append_char(init);
}

void	msh_append_char(t_input *init)
{
	size_t	j;
	char	*str;

	if (init->i == 0)
	{
		msh_init_pipeline(init);
		return ;
	}
	j = 0;
	while (init->pipeline[init->pipe_count][init->token_count][j])
		j++;
	str = (char *)malloc(sizeof(char) * (j + 2));
	if (!str)
		msh_close_on_error(init);
	j = 0;
	while (init->pipeline[init->pipe_count][init->token_count][j])
	{
		str[j] = init->pipeline[init->pipe_count][init->token_count][j];
		j++;
	}
	str[j] = init->string[init->i];
	str[j + 1] = 0;
	free(init->pipeline[init->pipe_count][init->token_count]);
	init->pipeline[init->pipe_count][init->token_count] = str;
}
