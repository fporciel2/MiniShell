/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_set_signals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 08:57:13 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/30 09:05:20 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* <one line to give the program's name and a brief idea
 * of what it does.>
 * Copyright (C) <year>  <name of author>
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
 * <your contact information here>
 */

#include "minishell.h"

static void	msh_close_on_error(t_input *init)
{
	init->envp = msh_clean_cmd(init->envp);
	free(init);
	exit(EXIT_FAILURE);
}

void	msh_handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	msh_handle_sigquit(int sig)
{
	(void)sig;
}

void	msh_initialize(t_input *init)
{
}

void	msh_set_signals(t_input *init)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	msh_initialize(init);
	sa_int.sa_handler = msh_handle_sigint;
	if (sigemptyset(&sa_int.sa_mask) < 0)
		msh_close_on_error(init);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) < 0)
		msh_close_on_error(init);
	sa_quit.sa_handler = msh_handle_sigquit;
	if (sigemptyset(&sa_quit.sa_mask) < 0)
		msh_close_on_error(init);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) < 0)
		msh_close_on_error(init);
}
