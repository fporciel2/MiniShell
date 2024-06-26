/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:21:09 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/29 17:09:23 by fporciel         ###   ########.fr       */
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

int	msh_error(char *str1, char *str2, char *str3)
{
	int	i;

	i = 0;
	if (str1)
		i = (int)write(2, str1, msh_strlen(str1));
	if (str2)
		i += (int)write(2, str2, msh_strlen(str2));
	if (str3)
		i += (int)write(2, str3, msh_strlen(str3));
	i += (int)write(2, "\n", 1);
	i = 0;
	return (i);
}
