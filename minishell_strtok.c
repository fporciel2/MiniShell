/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_strtok.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:19:59 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/24 08:22:38 by fporciel         ###   ########.fr       */
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

static int	msh_normalize(t_input *init)
{
	if (!init->i || (init->line[init->i - 1] <= 32)
		|| (init->line[init->i - 1] == 60) || (init->line[init->i - 1] == 62)
		|| (init->line[init->i - 1] == 124))
		return (msh_new_token(init));
	return (msh_new_char(init));
}

static void	msh_slide_delimiters(t_input *init)
{
	if (init->i == 0)
		init->space = 1;
	else
		init->space = 0;
	while (init->line[init->i] && (init->line[init->i] <= 32))
		init->i++;
	init->i--;
}

static int	msh_redirtok(t_input *init)
{
	char	redir;

	redir = init->line[init->i];
	init->errtok = msh_new_token(init);
	if (init->errtok)
		return (perror("Error"), 0);
	if (init->line[init->i + 1] == redir)
	{
		init->redirflag = 1;
		init->i++;
		init->errtok = msh_new_char(init);
		if (init->errtok)
			return (perror("Error"), 0);
		init->redirflag = 0;
		if ((redir == 60) && (init->line[init->i] == 60))
			return (1);
	}
	return (init->heredoc);
}

static int	msh_quoting(t_input *init)
{
	char	quote;

	quote = init->line[init->i];
	if (init->i && (init->line[init->i - 1] <= 32) && init->line[init->i - 1])
		init->pipe = msh_new_token(init);
	else
		init->pipe = msh_new_char(init);
	init->errquote = 0;
	init->i++;
	while (!init->errtok && init->line[init->i] && init->line[init->i] != quote)
	{
		init->pipe = msh_new_char(init);
		if (init->errtok)
			return (perror("Error"), 0);
		init->i++;
	}
	if (init->errtok || !init->line[init->i])
		return (0);
	else
		init->errtok = msh_new_char(init);
	return (1);
}

int	msh_strtok(t_input *init)
{
	if (!init->line || !*init->line)
		return (0);
	while (init->line[init->i])
	{
		if ((init->line[init->i] == 34) || (init->line[init->i] == 39))
			init->errquote = msh_quoting(init);
		else if ((init->line[init->i] == 60) || (init->line[init->i] == 62))
			init->heredoc = msh_redirtok(init);
		else if ((init->line[init->i] <= 32) && (init->line[init->i] > 0))
			msh_slide_delimiters(init);
		else if (init->line[init->i] == 124)
			init->pipe = msh_new_token(init);
		else
			init->errtok = msh_normalize(init);
		if (init->errtok || (!init->toks && !init->space))
			return (perror("Error"), 0);
		if (init->line[init->i])
			init->i++;
	}
	if (!init->errquote)
		return (write(2, "Syntax error: unclosed quotes\n", 30), 0);
	return (msh_parser(init));
}
