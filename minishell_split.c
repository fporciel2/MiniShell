/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:51:53 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/25 15:09:31 by fporciel         ###   ########.fr       */
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

static int	msh_set_new_token(t_input *init, char **matrix, char ***container,
		size_t j)
{
	if (matrix)
	{
		matrix[j] = (char *)malloc(sizeof(char) * 2);
		if (!matrix[j])
			return (0);
		matrix[j][1] = 0;
		matrix[j][0] = init->string[init->i];
	}
	if (container)
	{
		container[j] = (char **)malloc(sizeof(char *) * 2);
		if (!container[j])
			return (0);
		container[j][1] = NULL;
		container[j][0] = (char *)malloc(sizeof(char) * 2);
		if (!container[j][0])
			return (free(container[j]), 0);
		container[j][0][1] = 0;
		container[j][0][0] = init->string[init->i];
	}
	return (1);
}

static int	msh_init_pipeline(t_input *init)
{
	init->pipeline = (char ***)malloc(sizeof(char **) * 2);
	if (!init->pipeline)
		return (0);
	init->pipeline[1] = NULL;
	init->pipeline[0] = (char **)malloc(sizeof(char *) * 2);
	if (!init->pipeline[0])
		return (free(init->pipeline), 0);
	init->pipeline[0][1] = NULL;
	init->pipeline[0][0] = (char *)malloc(sizeof(char) * 2);
	if (!init->pipeline[0][0])
		return (free(init->pipeline[0]), free(init->pipeline), 0);
	init->pipeline[0][0][1] = 0;
	init->pipeline[0][0][0] = init->string[init->i];
	init->pipe_count = 0;
	init->token_count = 0;
	return (1);
}

int	msh_split_pipeline(t_input *init)
{
	char	***container;
	size_t	j;

	if (init->i == 0)
		return (msh_init_pipeline(init));
	j = 0;
	container = (char ***)malloc(sizeof(char **) * (init->pipe_count + 3));
	if (!container)
		return (0);
	init->pipe_count++;
	while (init->pipeline[j])
	{
		container[j] = init->pipeline[j];
		j++;
	}
	container[j + 1] = NULL;
	if (!msh_set_new_token(init, NULL, container, j))
		return (0);
	init->token_count = 0;
	msh_split_clean_pipeline(init);
	init->pipeline = container;
	return (1);
}

int	msh_split_token(t_input *init)
{
	char	**matrix;
	size_t	j;

	if (init->i == 0)
		return (msh_init_pipeline(init));
	j = 0;
	matrix = (char **)malloc(sizeof(char *) * (init->token_count + 3));
	if (!matrix)
		return (0);
	init->token_count++;
	while (init->pipeline[init->pipe_count][j])
	{
		matrix[j] = init->pipeline[init->pipe_count][j];
		j++;
	}
	matrix[j + 1] = NULL;
	if (!msh_set_new_token(init, matrix, NULL, j))
		return (0);
	msh_split_clean_command(init->pipeline[init->pipe_count]);
	init->pipeline[init->pipe_count] = matrix;
	return (1);
}

int	msh_append_char(t_input *init)
{
	size_t	j;
	char	*str;

	if (init->i == 0)
		return (msh_init_pipeline(init));
	j = 0;
	while (init->pipeline[init->pipe_count][init->token_count][j])
		j++;
	str = (char *)malloc(sizeof(char) * (j + 2));
	if (!str)
		return (0);
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
	return (1);
}
