/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansions_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 06:42:46 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/18 07:49:04 by fporciel         ###   ########.fr       */
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

void	msh_interrupt_expansion(t_input *init, char *str, char **mat)
{
	if (str)
		free(str);
	if (mat)
		free(mat);
	init->err_xpand = 0;
}

ssize_t	msh_is_env(char *str, ssize_t i, char **envp)
{
	ssize_t	j;
	ssize_t	k;
	ssize_t	l;

	j = 0;
	if (!envp)
		return (0);
	while (envp[j])
	{
		k = (i + 1);
		l = 0;
		while (str[k] && envp[j][l] && (str[k] == envp[j][l])
				&& (envp[j][l] != 61) && (str[k] != 34) && (str[k] != 39)
				&& (str[k] > 32))
		{
			k++;
			l++;
		}
		if (envp[j][l] == 61)
			return (j);
		j++;
	}
	return (0);
}

int	msh_is_exp(char *str, ssize_t i)
{
	if ((str[i + 1] == 34) || (str[i + 1] == 39) || (str[i + 1] < 32))
		return (0);
	return (1);
}
