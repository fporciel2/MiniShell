/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_is_in_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:59:57 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/17 18:16:00 by fporciel         ###   ########.fr       */
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

int	msh_is_in_quotes(char *str, ssize_t i)
{
	ssize_t	j;
	char	flag;

	j = 0;
	flag = 0;
	while (j != i)
	{
		if ((str[j] == 39) || (str[j] == 34))
		{
			if (flag == 0)
				flag = str[j];
			else if (flag == str[j])
				flag = 0;
		}
		j++;
	}
	return ((int)flag);
}

int	msh_is_in_single_quotes(char *str, ssize_t i)
{
	char	flag;

	flag = (char)msh_is_in_quote(str, i);
	return (flag == 39);
}
