/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unquote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:31:56 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/11 19:08:24 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* `MiniShell' is a simple shell for Debian GNU/Linux.
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

char	*msh_unquote_name(t_input *init, int param)
{
	ssize_t	i;
	char	*str;
	char	quote;

	if (param == 0)
		str = init->cmds[init->i].cmd_name;
	else
		str = init->cmds[init->i].cmd_argv[init->j];
	i = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == 34) || (str[i] == 39))
		{
			quote = str[i];
			str = msh_replace_string(init, quote);
			init->pipeline[init->i][init->j + 1] = init->cmds[init->i].cmd_name;
			i = 0;
			continue ;
		}
		i++;
	}
	return (str);
}
