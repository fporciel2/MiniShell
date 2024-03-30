/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_new_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:24:18 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/30 17:31:12 by fporciel         ###   ########.fr       */
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

char	*msh_new_token(t_input *init)
{
	char	*token;

	token = (char *)malloc(sizeof(char) * 2);
	if (!token)
		return (NULL);
	token[0] = init->line[init->i];
	token[1] = 0;
	return (token);
}

char	**msh_new_command(t_input *init)
{
	char	**command;

	command = (char **)malloc(sizeof(char *) * 2);
	if (!command)
		return (NULL);
	command[0] = msh_new_token(init);
	if (!command[0])
		return (free(command), NULL);
	command[1] = NULL;
	return (command);
}
