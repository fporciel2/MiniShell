/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:48:11 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/22 14:27:38 by fporciel         ###   ########.fr       */
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

static void	msh_no_readline(t_input *init)
{
	msh_loop_clean_all(init);
	rl_clear_history();
	if (write(1, "\n", 1) < 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	msh_loop(t_input *init)
{
	while (42)
	{
		msh_loop_memset(init);
		init->string = readline("minishell> ");
		if (init->string == NULL)
			msh_no_readline(init);
		if (*init->string)
			add_history(init->string);
		else
		{
			free(init->string);
			continue ;
		}
		if (!msh_strtok(init) || !msh_syntax(init) || !msh_semantics(init)
			|| !msh_execution(init))
			msh_loop_close_on_error(init);
	}
}
