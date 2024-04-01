/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_strtok.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:19:00 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/01 12:49:45 by fporciel         ###   ########.fr       */
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

static void	msh_slide_delimiters(t_input *init)
{
	if (init->i == 0)
		init->space_flag = 1;
	else
		init->space_flag = 0;
	while ((init->line[init->i] == 9) || (init->line[init->i] == 10)
				|| (init->line[init->i] == 32))
		init->i++;
	init->i--;
}

static int	msh_redirecting(t_input *init)
{
	char	redir;

	redir = init->line[init->i];
	init->pipeline = msh_append_token(init);
	if (!init->pipeline)
		return (strerror(errno), 0);
	init->i++;
	if (init->line[init->i] == redir)
	{
		init->pipeline = msh_append_char(init);
		if (!init->pipeline)
			return (strerror(errno), 0);
		if ((redir == 60) && (init->line[init->i] == 60) && !init->pipe)
			return (HEREDOC);
		else if ((redir == 60) && (init->line[init->i] == 60) && init->pipe)
			return (PIPE_HEREDOC);
	}
	else
		init->i--;
	return (0);
}

static int	msh_quoting(t_input *init)
{
	char	quote;

	quote = init->line[init->i];
	init->pipeline = msh_append_token(init);
	init->errquote = 1;
	if (!init->pipeline)
		return (strerror(errno), 0);
	init->i++;
	while (init->line[init->i] && (init->line[init->i] != quote))
	{
		init->pipeline = msh_append_char(init);
		if (!init->pipeline)
			return (strerror(errno), 0);
		init->i++;
	}
	if (!init->line[init->i])
		return (1);
	else
		init->pipeline = msh_append_char(init);
	if (!init->pipeline)
		return (strerror(errno), 0);
	return (0);
}

int	msh_strtok(t_input	*init)
{
	init->i = 0;
	init->space_flag = 0;
	init->errquote = 0;
	init->heredoc = 0;
	init->pipe = 0;
	while (init->line[init->i])
	{
		if ((init->line[init->i] == 34) || (init->line[init->i] == 39))
			init->errquote = msh_quoting(init);
		else if ((init->line[init->i] == 60) || (init->line[init->i] == 62))
			init->heredoc = msh_redirecting(init);
		else if ((init->line[init->i] == 9) || (init->line[init->i] == 10)
				|| (init->line[init->i] == 32))
			msh_slide_delimiters(init);
		else if (init->line[init->i] == 124)
			init->pipeline = msh_append_command(init);
		else
			init->pipeline = msh_append_char(init);
		if (!init->pipeline && !init->space_flag)
			return (strerror(errno), 0);
		if (init->line[init->i])
			init->i++;
	}
	printf("ERRQUOTE: %d\n", init->errquote);
	if (init->heredoc == HEREDOC)
		printf("HEREDOC: %d\n", init->heredoc);
	else if (init->heredoc == PIPE_HEREDOC)
		printf("PIPE_HEREDOC: %d\n", init->heredoc);
	if (init->pipe == 1)
		printf("NORMAL PIPES: %d\n", init->pipe);
	else if (init->pipe == PIPE)
		printf("UNCLOSED PIPE: %d\n", init->pipe);
	return (1);
}
