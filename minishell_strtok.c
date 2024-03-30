/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_strtok.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:19:00 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/30 11:54:57 by fporciel         ###   ########.fr       */
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

int	msh_strtok(t_input	*init)
{
	init->i = 0;
	init->quotation = 0;
	while (init->line[i])
	{
		if ((init->line[i] == 34) || (init->line[i] == 39))
			init->quotation = msh_quoting(init);
		else if ((init->line[i] == 60) || (init->line[i] == 62))
			init->heredoc = msh_redirecting(init);
		else if ((init->line[i] == 9) || (init->line[i] == 10)
				|| (init->line[i] == 32))
			init->pipeline = msh_append_token(init);
		else if (init->line[i] == 124)
			init->pipeline = msh_append_command(init);
		else
			init->pipeline = msh_append_char(init);
		if (!init->pipeline)
			return (strerror(errno), 0);
		init->i++;
	}
}
