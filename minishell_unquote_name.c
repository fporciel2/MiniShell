/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unquote_name.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:43:29 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/12 16:22:22 by fporciel         ###   ########.fr       */
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
 */

#include "minishell.h"

static int	msh_check_quotes(char *str)
{
	ssize_t	i;
	char	quote_flag;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[i] == 34) || (str[i] == 39))
		{
			quote_flag = str[i++];
			while (str[i] && (str[i] != quote_flag))
				i++;
			if (str[i] == quote_flag)
				return (1);
			else
				return (2);
		}
		i++;
	}
	return (0);
}

static void	msh_unslide(char *str, char *new, ssize_t *i, ssize_t *j)
{
	char	flag;

	if (!str[*i])
		return ;
	flag = str[*i];
	(*i)++;
	while (str[*i] && (str[*i] != flag))
	{
		new[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	if (str[*i])
	{
		(*i)++;
		while (str[*i])
		{
			new[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
	}
}

static void	msh_slide(char *str, char *new, ssize_t *i, ssize_t *j)
{
	while (str[*i] && (str[*i] != 34) && (str[*i] != 34))
	{
		new[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
}

static char	*msh_unquote(char *str)
{
	ssize_t	i;
	ssize_t	j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (msh_strlen(str) - 1));
	if (!new)
		return (str);
	msh_slide(str, new, &i, &j);
	msh_unslide(str, new, &i, &j);
	return (new);
}

char	*msh_unquote_name(t_input *init)
{
	char	*str;

	str = init->cmds[init->i].cmd_name;
	while (msh_check_quotes(str) == 1)
	{
		str = init->cmds[init->i].cmd_name;
		str = msh_unquote(str);
		init->pipeline[init->i][0] = str;
		free(init->cmds[init->i].cmd_name);
		init->cmds[init->i].cmd_name = str;
	}
	if (msh_check_quotes(str) == 2)
		init->errquote = 1;
	return (str);
}
