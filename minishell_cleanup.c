/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:49:18 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/29 17:03:50 by fporciel         ###   ########.fr       */
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

char	*msh_clean_str(char *str)
{
	if (!str)
		return (NULL);
	free(str);
	return (NULL);
}

char	**msh_clean_matrix(char **mat)
{
	ssize_t	i;

	if (!mat)
		return (NULL);
	i = 0;
	while (mat[i])
		i++;
	i--;
	while (i >= 0)
	{
		mat[i] = msh_clean_str(mat[i]);
		i--;
	}
	free(mat);
	return (NULL);
}
