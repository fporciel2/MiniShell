/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 07:13:28 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/22 07:21:08 by fporciel         ###   ########.fr       */
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

int	msh_get_matrix(char **source, char ***dest)
{
	ssize_t	i;

	if (!source || !*source)
		return (0);
	*dest = (char **)malloc(sizeof(char *) * (msh_matlen(source) + 1));
	if (!*dest)
		return (0);
	i = 0;
	while (source[i])
	{
		(*dest)[i] = msh_strdup(source[i]);
		if (!(*dest)[i])
			return (msh_matdel(dest), 0);
		i++;
	}
	(*dest)[i] = NULL;
	return (1);
}
