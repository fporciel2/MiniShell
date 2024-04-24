/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:41:16 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/24 12:18:20 by fporciel         ###   ########.fr       */
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

int	msh_new_command(t_input *init, t_tok *tok)
{
	t_cmd	*new;
	t_cmd	*tmp;

	tmp = init->cmds;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return (perror("Error"), 1);
	new->name = msh_strdup(tok->str);
	if (!new->name)
		return (perror("Error"), 1);
	new->argv = NULL;
	new->envp = init->envp;
	new->next = NULL;
	new->redir = 0;
	if (!tmp)
		init->cmds = new;
	else
		tmp->next = new;
	new->prev = tmp;
	return (0);
}

static int	msh_arg_setting2(t_input *init, t_tok *tok, t_cmd *cmd)
{
	char	**new;
	ssize_t	i;

	new = (char **)malloc(sizeof(char *) * (msh_matlen(cmd->argv) + 1));
	if (!new)
		return (perror("Error"), 1);
	i = 0;
	while (cmd->argv[i])
	{
		new[i] = msh_strdup(cmd->argv[i]);
		if (!new[i])
			return (perror("Error"), 1);
		i++;
	}
	new[i] = msh_strdup(tok->str);
	if (!new[i])
		return (perror("Error"), 1);
	new[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new;
	return (0);
}

static int	msh_arg_setting(t_input *init, t_tok *tok, t_cmd *cmd)
{
	char	**new;

	if (!cmd->argv)
	{
		new = (char **)malloc(sizeof(char *) * 3);
		if (!new)
			return (perror("Error"), 1);
		new[0] = msh_strdup(cmd->name);
		if (!new[0])
			return (perror("Error"), 1);
		new[1] = msh_strdup(tok->str);
		if (!new[1])
			return (perror("Error"), 1);
		new[2] = NULL;
		cmd->argv = new;
	}
	else
		return (msh_arg_setting2(init, tok, cmd));
	return (0);
}

int	msh_new_arg(t_input *init, t_tok *tok)
{
	t_cmd	*tmp;

	tmp = init->cmds;
	if (!tmp)
		return (msh_new_command(init, tok));
	while (tmp->next)
		tmp = tmp->next;
	if (!tmp->name)
	{
		if (msh_new_command(init, tok))
			return (1);
	}
	return (msh_arg_setting(init, tok, tmp));
}

int	msh_new_redir(t_input *init, t_tok *tok)
{
	t_cmd	*tmp;

	if (msh_check_redir(tok))
		return (1);
	tmp = init->cmds;
	if ((tok->prev && tok->prev->type == 1) || (!tok->prev))
	{
		if (msh_new_command(init, tok))
			return (1);
		while (tmp->next)
			tmp = tmp->next;
		free(tmp->name);
		tmp->name = NULL;
		tmp->redir = 1;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->redir = 1;
	return (0);
}
