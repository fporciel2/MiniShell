/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokcmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:30:14 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/16 16:30:04 by fporciel         ###   ########.fr       */
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

static char	**msh_copy_cmd(t_input *init)
{
	char	**tmp;
	char	**tmp1;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	tmp = init->pipeline[init->i];
	tmp++;
	if (init->i != 0)
		tmp++;
}

static char	*msh_copy_name(t_input *init)
{
	char	*name;
	char	**tmp;
	ssize_t	i;

	i = 0;
	tmp = init->pipeline[init->i];
	if (init->i != 0)
		tmp++;
	name = (char *)malloc(sizeof(char) * (msh_strlen(*tmp) + 1));
	if (name == NULL)
		return (NULL);
	if (tmp[0][0] == 0)
		return (free(name), NULL);
	while (tmp[0][i])
	{
		name[i] = tmp[0][i];
		i++;
	}
	name[i] = 0;
	return (name);
}

static t_cmd	*msh_lstcmds(t_cmd *prev, ssize_t cmdlen)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->name = msh_copy_name(init);
	if (!new->name)
		return (free(new), NULL);
	new->argv = msh_copy_cmd(init);
	if (!new->argv)
		return (free(new->name), free(new), NULL);
	new->envp = init->envp;
	new->next = NULL;
	new->prev = prev;
	return (new);
}

int	msh_tokcmd(t_input *init)
{
	t_cmd	*tmp;
	
	init->i = -1;
	init->cmds = NULL;
	while (init->pipeline[++init->i])
	{
		init->cmdlen = msh_cmdlen(init->pipeline[init->i]);
		if (!init->cmds)
		{
			tmp = msh_lstcmds(NULL, init->cmdlen, init);
			init->cmds = tmp;
		}
		else
		{
			tmp->next = msh_lstcmds(tmp, init->cmdlen, init);
			tmp = tmp->next;
		}
		tmp->envp = init->envp;
		if (!tmp || msh_parsing(init->cmds, init))
			return (0);
	}
	return (1);
}
