/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 07:59:49 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/24 04:46:21 by fporciel         ###   ########.fr       */
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

int	msh_loop(t_input *init)
{
	int	exit_status;

	exit_status = 0;
	init->exit_flag = 0;
	msh_init(init);
	while (42)
	{
		msh_memset(init);
		init->line = readline("MiniShell> ");
		if (!init->line)
		{
			exit_status = init->exit_flag;
			init->i = write(1, "exit\n", 5);
			msh_clean_init(&init);
			break ;
		}
		else if (*init->line)
			add_history(init->line);
		else
			continue ;
		if (!msh_strtok(init))
			continue ;
	}
	return (exit_status);
}
