/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokcmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:30:14 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/04 10:26:35 by fporciel         ###   ########.fr       */
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
 * https://github.com/MiniShell
 *
 * GENERAL CONCEPTS OF ´TOKCMD´ FUNCTIONS SET
 *
 * According to Bash's manual, after tokenization the tokens are parsed into
 * simple commands. Since, the MiniShell's tokenizer doesn't perform
 * quote removal in place, that operation is performed in the ´tokcmd´
 * functions' set. This program doesn't handle the unclosed quotes case: so, if
 * a quote is not closed, the program gives a syntax error.
 *
 * Furthermore, the program does not handle lists of commands or compund
 * commands: so, the only construct taken into account is the ´pipeline´, which
 * is partially handled by the tokenizer, that already divides the pipeline into
 * tokens. Since there are no reserved words in MiniShell, pipelines' syntax
 * doesn't handle the ´time´ word and the related constructs. So, this set of
 * functions only splits the pipeline into a linked list of commands, removing
 * the quotes, checks for the correctness of the pipeline's syntax and frees the
 * memory allocated by the tokenizer.
 *
 * `MiniShell` does not handle: aliases, keywords, varibles assignment,
 * functions and command substitutions. So, the syntax of a simple command is
 * `command [arguments]`.
 */

#include "minishell.h"

static void	msh_set_cmds(t_input *init)
{
	while (init->pipeline[init->i])
	{
		init->cmds[init->i].cmd_name = init->pipeline[init->i][0];
		init->cmds[init->i].cmd_argv = init->pipeline[init->i] + 1;
		init->cmds[init->i].cmd_envp = init->envp;
		init->cmds[init->i].cmd_argc = msh_cmdlen(init->pipeline[init->i]);
		init->cmds[init->i].cmd_id = init->i + 1;
		init->i++;
	}
	init->cmds[init->i].cmd_name = NULL;
	init->cmds[init->i].cmd_argv = NULL;
	init->cmds[init->i].cmd_envp = NULL;
	init->cmds[init->i].cmd_argc = 0;
	init->cmds[init->i].cmd_id = 0;
}

int	msh_tokcmd(t_input *init)
{
	if (init->errquote)
	{
		init->i = write(2, ERRQUOTE, 42);
		return (0);
	}
	init->cmdlen = msh_pipelen(init->pipeline);
	init->cmds = (t_cmd *)malloc(sizeof(t_cmd) * (init->cmdlen + 1));
	if (!init->cmds)
		return (strerror(errno), 0);
	init->i = 0;
	init->j = 0;
	msh_set_cmds(init);
	return (1);
}
