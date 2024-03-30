/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:15:05 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/30 16:42:10 by fporciel         ###   ########.fr       */
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

char	***msh_append_token(t_input *init)
{
	ssize_t	pipelen;
	ssize_t	cmdlen;
	char	**new;

	if (init->i == 0)
		return (msh_start_tokenization(init));
	pipelen = msh_pipelen(init->pipeline);
	cmdlen = msh_cmdlen(init->pipeline[pipelen]);
	new = (char **)malloc(sizeof(char *) * (cmdlen + 2));
	if (!new)
		return (msh_clean_pipeline(init->pipeline));
	cmdlen = 0;
	while (init->pipeline[pipelen][cmdlen])
	{
		new[cmdlen] = init->pipeline[pipelen][cmdlen];
		cmdlen++;
	}
	new[cmdlen] = msh_new_token(init);
	if (!new[cmdlen])
		return (msh_clean_pipeline(init->pipeline));
	new[cmdlen + 1] = NULL;
	free(init->pipeline[pipelen]);
	init->pipeline[pipelen] = new;
	return (init->pipeline);
}

char	***msh_append_command(t_input *init)
{
	ssize_t	pipelen;
	char	***new;

	if (init->i == 0)
		return (msh_start_tokenization(init));
	pipelen = msh_pipelen(init->pipeline);
	new = (char ***)malloc(sizeof(char **) * (pipelen + 2));
	if (!new)
		return (msh_clean_pipeline(init->pipeline));
	pipelen = 0;
	while (init->pipeline[pipelen])
	{
		new[pipelen] = init->pipeline[pipelen];
		pipelen++;
	}
	new[pipelen] = msh_new_command(init);
	if (!new[pipelen])
		return (msh_clean_pipeline(init->pipeline));
	new[pipelen + 1] = NULL;
	free(init->pipeline);
	return (new);
}
