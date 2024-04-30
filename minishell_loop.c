/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:26:46 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/30 16:19:04 by fporciel         ###   ########.fr       */
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

int	msh_destroy(t_msh *msh, int param)
{
	if (param)
		msh->envp = msh_clean_matrix(msh->envp);
	if (msh->input)
		msh->input = msh_clean_str(msh->input);
	return (msh->exit);
}

int	msh_print_exit(int exit)
{
	int	code;

	if (exit == 0)
		exit = 1;
	code = (int)write(1, "exit\n", 5);
	code = exit;
	return (code);
}

int	msh_set_memory(t_msh *msh)
{
	msh->exit = msh_destroy(msh, 0);
	return (msh->exit);
}

int	msh_loop(t_msh *msh)
{
	while (!msh->exit)
	{
		msh->exit = msh_set_memory(msh);
		msh->input = readline("minishell> ");
		if (!msh->input)
			msh->exit = msh_print_exit(msh->exit);
		else if (!(*msh->input))
			continue ;
		else
		{
			add_history(msh->input);
			if (!msh_input(msh))
				continue ;
		}
	}
	return (msh_destroy(msh, 1));
}
