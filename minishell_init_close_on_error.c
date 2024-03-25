/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init_close_on_error.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:09:18 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/25 10:28:51 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ´MiniShell´ is a simple shell for Debian GNU/Linux.
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

static void	msh_remove_envs(t_input *init)
{
	ssize_t	i;

	i = 0;
	if (init->envp)
	{
		while (init->envp[i])
			i++;
		i--;
		while (i >= 0)
		{
			free(init->envp[i]);
			i--;
		}
		free(init->envp);
	}
}

void	msh_init_close_on_error(t_input *init)
{
	msh_remove_envs(init);
	free(init);
	rl_clear_history();
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}
