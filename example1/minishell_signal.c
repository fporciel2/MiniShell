/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 07:48:01 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/22 07:53:21 by fporciel         ###   ########.fr       */
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

void	msh_handle_sigint(int sig)
{
	ssize_t	i;

	(void)sig;
	i = write(STDOUT_FILENO, "\n", 1);
	(void)i;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	msh_set_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = msh_handle_sigint;
	if (sigemptyset(&sa_int.sa_mask) < 0)
		return (perror("Error"), 0);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) < 0)
		return (perror("Error"), 0);
	sa_quit.sa_handler = SIG_IGN;
	if (sigemptyset(&sa_quit.sa_mask) < 0)
		return (perror("Error"), 0);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) < 0)
		return (perror("Error"), 0);
	return (1);
}
