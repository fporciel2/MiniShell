/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokcmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:30:14 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/17 14:25:41 by fporciel         ###   ########.fr       */
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

static int	msh_check_double_pipes(t_input *init)
{
	if ((init->cmds && (init->cmds->name[0] == 124))
		|| (init->i < msh_pipelen(init->pipeline)))
	{
		init->errquote = write(2, ERRPIPE, 42); 
		init->exit_status = 2;
	}
	return (0);
}

static char	**msh_copy_cmd(t_input *init)
{
	char	**tmp;
	char	**tmp1;
	ssize_t	i;

	i = 0;
	tmp = init->pipeline[init->i];
	if (init->i != 0)
		tmp++;
	if (!*tmp)
		return (NULL);
	tmp1 = (char **)malloc(sizeof(char *) * (msh_cmdlen(tmp) + 1));
	tmp1[0] = NULL;
	if (tmp1 == NULL)
		return (NULL);
	while (tmp[i])
	{
		tmp1[i] = msh_strdup(tmp[i]);
		if (tmp1[i] == NULL)
			return (NULL);
		i++;
	}
	tmp1[i] = NULL;
	return (tmp1);
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
	if (!*tmp)
		return (NULL);
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

static t_cmd	*msh_lstcmds(t_cmd *prev, t_input *init)
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
	new->argc = msh_cmdlen(new->argv);
	new->envp = init->envp;
	new->next = NULL;
	new->prev = prev;
	return (new);
}

int	msh_tokcmd(t_input *init)
{
	t_cmd	*tmp;
	t_cmd	*tmp1;
	
	init->i = -1;
	init->cmds = NULL;
	tmp = NULL;
	while (init->pipeline[++init->i])
	{
		if (!init->cmds)
		{
			tmp = msh_lstcmds(NULL, init);
			tmp->envp = init->envp;
			init->cmds = tmp;
		}
		else
		{
			tmp->next = msh_lstcmds(tmp, init);
			tmp->envp = init->envp;
			tmp = tmp->next;
		}
		if (!tmp || !msh_parsing(init->cmds, init))
			return (msh_check_double_pipes(init));
	}
	tmp1 = init->cmds;
	while (tmp1)
	{
		printf("COMMAND: %s\n\n", tmp1->name);
		ssize_t	i = 0;
		while (tmp1->argv[i])
		{
			printf("ARGUMENT: %s\n", tmp1->argv[i]);
			i++;
		}
		printf("\n\n");
		tmp1 = tmp1->next;
	}
	return (1);
}
