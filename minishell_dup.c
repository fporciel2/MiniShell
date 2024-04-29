/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:39:50 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/29 16:47:54 by fporciel         ###   ########.fr       */
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

char	*msh_strdup(char *str)
{
	char	*new;
	ssize_t	i;

	if (!str)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (msh_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

char	**msh_matdup(char **mat)
{
	ssize_t	i;
	char	**new;

	if (!mat)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (msh_matlen(mat) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (mat[i])
	{
		new[i] = msh_strdup(mat[i]);
		if (!new[i])
			return (msh_clean_matrix(&new, msh_error(SYS_CALL_ERROR,
					strerror(errno), NULL)));
		i++;
	}
	new[i] = NULL;
	return (new);
}
