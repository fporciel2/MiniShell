/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:25:24 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/30 09:46:57 by fporciel         ###   ########.fr       */
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

static void	msh_memset(t_input *init)
{
	init->pipeline = msh_clean_pipeline(init->pipeline);
	init->line = msh_clean_str(init->line);
}

static void	msh_free_init(t_input *init)
{
	init->envp = msh_clean_cmd(init->envp);
	init->pipeline = msh_clean_pipeline(init->pipeline);
	init->line = msh_clean_str(init->line);
	init->prompt = NULL;
	free(init);
}

void	msh_loop(t_input *init)
{
	while (42)
	{
		msh_memset(init);
		init->line = readline("MiniShell> ");
		if (!init->line)
		{
			msh_free_init(init);
			break ;
		}
		else if (*init->line)
			add_history(init->line);
		else
			continue ;
	}
}
