/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:29:22 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/22 10:59:34 by fporciel         ###   ########.fr       */
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

static const t_input	*g_init;

void	msh_handle_sigint(int sig)
{
	t_input	*init;

	(void)sig;
	init = g_init;
	if (write(STDOUT_FILENO, "\n", 1) < 0)
		msh_handle_sigint_close_on_error(init);
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
	init->string = NULL;
	init->pipeline = NULL;
	init->pipe_count = START;
	init->token_count = START;
	init->i = START;
	init->open_quote = START;
	init->quote_state = START;
	init->pipe_state = START;
}

void	msh_init(char **envp, t_input *init)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	
	init->envp = envp;
	g_init = init;
	sa_int.sa_handler = msh_handle_sigint;
	if (sigemptyset(&sa_int.sa_mask) < 0)
		msh_init_close_on_error(init);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) < 0)
		msh_init_close_on_error(init);
	sa_quit.sa_handler = msh_handle_sigquit;
	if (sigemptyset(&sa_quit.sa_mask) < 0)
		msh_init_close_on_error(init);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) < 0)
		msh_init_close_on_error(init);
	msh_initialize(init);
}
