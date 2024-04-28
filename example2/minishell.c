/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 06:17:49 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/18 12:25:31 by fporciel         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_input	*init;
	int		exit_minishell;

	if (argc != 1)
	{
		errno = write(2, "Do not use arguments if you want to live!\n", 42);
		return (errno);
	}
	init = (t_input *)malloc(sizeof(t_input));
	if (!init)
		return (perror("Error"), errno);
	init->prompt = argv[0];
	if (!msh_get_envp(envp, init))
		return (free(init), perror("Error"), errno);
	msh_set_signals(init);
	exit_minishell = msh_loop(init);
	return (exit_minishell);
}
